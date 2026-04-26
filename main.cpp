#include "raylib.h"
#include <string>
#include "string.h"
#include "math.h"
#include "stdbool.h"
#include <vector>
#include <unordered_map>

 

// ************* OBJEKT **************************
class Light_source{
    public:
        int x,y,strenght;
        std::vector<int> rays;
    Light_source(int x, int y, int strenght){
        this->x = x;
        this->y = y;
        this->strenght = strenght;
    }
};
class Objekt{
public:
    int x1, x2, y1, y2;
    Objekt(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    bool point_is_within(int x,int y){
        return (x > x1 && x < x2 && y > y1 && y < y2);
    }
    void draw(){
        DrawRectangle(x1,y1,x2-x1,y2-y1,BLUE);
    }
};

class Ray_of_light{
public:
    float dist;
    int light;
    Color color;
    int end_X;
    int end_y;
    Ray_of_light(){
        this->dist = 0;
        this->light = 0;
        this->color = BLANK;
    }
    void set_dist(float dist){
        this->dist = dist;
    }
    void set_color(Color color){
        this->color = color;
    }
    void set_ligt(int light){
        this->dist = light;
    }
    void set_endpoint(int x, int y){
        this->end_X = x;
        this->end_y = y;
    }
};

//****************** FUNKTIONS DEKLARATIONER ******************

void display_int_text(const char* input_text,int var,int x, int y);
void check_inputs();
void draw_rays(int fov, int rays, int x, int y,std::vector<Ray_of_light>& list);
void draw_objects();
bool reached_object(float current_x, float current_y);
void render_rays();
void setLightSource(Light_source lamp);
std::string GetKey(int x, int y);
void draw_light_rays(int fov, int rays, int x, int y,std::vector<Ray_of_light>& list);
void init_grid();
std::string GetKey(int x, int y);

//****************************PUBLIKA VARIABLER ***************** */
const int screen_x = 800;
const int screen_y = 800;

int player_radius = 20;

int player_x = 100;
int player_y = 100; 

float direction = 0;

int fov = 90;
int amount_of_rays = 800;
std::unordered_map<std::string, int> grid;

std::vector<Objekt> list_of_objects;

std::vector<Ray_of_light> rays;

int amount_of_light_rays = 800*4;

int max_dist = (int)sqrt(screen_x*screen_x+screen_y*screen_y);

/****************MAIN*************************** */
int main() 
{
    
    InitWindow(screen_x, screen_y, "Mitt spel");
    SetTargetFPS(60);

    // Skapa objekt
    int border_width = 20;
    

    list_of_objects.push_back(Objekt(0,0,screen_x,border_width));
    list_of_objects.push_back(Objekt(screen_x-border_width,0,screen_x,screen_y));
    list_of_objects.push_back(Objekt(0,screen_y-border_width,screen_x,screen_y));
    list_of_objects.push_back(Objekt(0,0,border_width,screen_y));
    
    list_of_objects.push_back(Objekt(200,200,300,300));
    
    Light_source lamp1 = Light_source(500,500,100);
    bool has_read_light = false;

    while (!WindowShouldClose()) 
    { 

        if (has_read_light == false){
            init_grid();
            draw_light_rays(360,4000,500,500,rays);
            has_read_light = true;
        }
        BeginDrawing(); 
        ClearBackground(RAYWHITE);
        check_inputs();
        Vector2 mousePos = GetMousePosition();
        display_int_text("Light level at mouse:", (int)grid[GetKey((int)mousePos.x,(int)mousePos.y)],50,100);
        display_int_text("direction",direction, 50, 50);
        display_int_text("x",player_x, 50, 70);
        display_int_text("y",player_y, 50, 90);
        draw_objects();
        //setLightSource(lamp1);
        DrawCircle(player_x,player_y,player_radius,RED);
        render_rays();
        draw_rays(fov,amount_of_rays,player_x,player_y, rays);

        

        
       
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
} 

void display_int_text(const char* input_text,int var, int x, int y){
    char text[32];
    sprintf(text,"%s: %d", input_text,var);
    DrawText(text,x,y,20,RED);
}

void check_inputs(){
    if (IsKeyDown(KEY_UP)){
        player_y += 5*cos(direction);
        player_x += 5*sin(direction);
    }
    if (IsKeyDown(KEY_DOWN)){
        player_y -= 5*cos(direction);
        player_x -= 5*sin(direction);
    }
    if (IsKeyDown(KEY_RIGHT)){
        direction -= PI/50;
    }
    if (IsKeyDown(KEY_LEFT)){
        direction += PI/50;
    }
    if (player_x > screen_x){
        player_x = screen_x;
    }
    if (player_y > screen_y){
        player_y = screen_y;
    }
    if (player_x < 0){
        player_x = 0;
    }
    if (player_y < 0){
        player_y = 0;
    }
}
void draw_rays(int fov, int rays, int x, int y,std::vector<Ray_of_light>& list){
    list.clear();
    for (int i = 0; i < rays; i++){
        float end_x = x;
        float end_y = y;
        while(!reached_object(end_x,end_y) && end_x > 0 && end_x < screen_x && end_y > 0 && y < screen_y){
            end_x += 1*sin(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
            end_y += 1*cos(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
        }
        float dist = sqrt((abs(x-end_x))*(abs(x-end_x))+(abs(y-end_y))*(abs(y-end_y)));
        Ray_of_light r = Ray_of_light();
        r.dist = dist;
        list.push_back(r);
        DrawLine(x,y,end_x,end_y,GREEN);
    }  
}

void draw_light_rays(int fov, int rays, int x, int y,std::vector<Ray_of_light>& list){
    list.clear();
    
    for (int i = 0; i < rays; i++){
        float end_x = x;
        float end_y = y;
        while(!reached_object(end_x,end_y) && end_x > 0 && end_x < screen_x && end_y > 0 && y < screen_y){
            end_x += 1*sin(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
            end_y += 1*cos(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
            float dist = sqrt((abs(x-end_x))*(abs(x-end_x))+(abs(y-end_y))*(abs(y-end_y)));
            grid[GetKey(end_x,end_y)] = (int) max_dist-dist; 
        }
        
        
        DrawLine(x,y,end_x,end_y,GREEN);
    }  
}


bool reached_object(float current_x, float current_y){
    for (Objekt &o: list_of_objects){
        if (o.point_is_within(current_x,current_y)){
            return true;
        }
    }
    return false;
}

void draw_objects(){
    for (Objekt &o : list_of_objects){
        o.draw();
    }
}

void render_rays(){
    int i = screen_x;
    
    //int line_len = screen_y-f;
    
    for (Ray_of_light &r: rays){
        int light_level = max_dist/grid[GetKey(r.end_X,r.end_y)]*100;
        int blueval = (int)(255 - light_level);
        int dist = r.dist;
        //int blueval = (int)(255 - r.dist/max_dist*150);
        Color c = (Color){0,0,blueval,255};
        DrawLine(i,0,i,dist/2,BLACK);
        DrawLine(i,dist/2,i,screen_y-dist/2,c);
        DrawLine(i,screen_y-dist/2,i,screen_y,BLACK);
        i--;
    }
}
void setLightSource(Light_source lamp){
    //draw_rays(360,amount_of_light_rays, lamp.x,lamp.y,temp);
}
std::string GetKey(int x, int y) {
    return std::to_string(x) + "," + std::to_string(y);
}
void init_grid(){
    for (int i = 0; i < screen_x; i++){
        for (int k = 0; k < screen_y; k++){
            grid[GetKey(i,k)] = 0;
        }
    }
}