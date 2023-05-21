#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen !!!DONE
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    float time = SDL_GetTicks()*0.01;
    /* x, y, theta coordinates */
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];
    
    SDL_Texture *texture = SDL_CreateTexture(gRenderer.get(),SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
    if( texture == NULL )
    {
        printf( "Unable to create streamable blank texture! SDL Error: %s\n", SDL_GetError() );
    }

    SDL_SetRenderTarget(gRenderer.get(),texture);
    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

    //tu zmienić na figure co chce
    SDL_RenderClear(gRenderer.get());
    SDL_SetRenderDrawColor(gRenderer.get(), 0x80, 0x80, 0x80, 0xFF);
    SDL_Rect body,noga_l,noga_p,pod_smigla_l,pod_smigla_p,smiglo_l,smiglo_p;
    int n;
    Sint16 punkty_x[6],punkty_x1[6],wzorek_x[8];
    punkty_x[0]=q_x-95+abs(90*sin(time));
    punkty_x[1]=q_x-60+abs(23*sin(time));
    punkty_x[2]=q_x-37-abs(23*sin(time));
    punkty_x[3]=q_x-5-abs(90*sin(time));
    punkty_x[4]=q_x-37-abs(23*sin(time));
    punkty_x[5]=q_x-60+abs(23*sin(time));

    punkty_x1[0]=q_x+abs(85*sin(time));
    punkty_x1[1]=q_x+30+abs(23*sin(time));
    punkty_x1[2]=q_x+53-abs(23*sin(time));
    punkty_x1[3]=q_x+85-abs(85*sin(time));
    punkty_x1[4]=q_x+53-abs(23*sin(time));
    punkty_x1[5]=q_x+30+abs(23*sin(time));

    wzorek_x[0]=q_x-70;
    wzorek_x[1]=q_x-50;
    wzorek_x[2]=q_x-30;
    wzorek_x[3]=q_x-10;
    wzorek_x[4]=q_x+10;
    wzorek_x[5]=q_x+30;
    wzorek_x[6]=q_x+50;
    wzorek_x[7]=q_x+70;
    Sint16 punkty_y[6],wzorek_y[8];
    punkty_y[0]=q_y-40;
    punkty_y[1]=q_y-50;
    punkty_y[2]=q_y-30;
    punkty_y[3]=q_y-40;
    punkty_y[4]=q_y-50;
    punkty_y[5]=q_y-30;

    wzorek_y[0]=q_y-15;
    wzorek_y[1]=q_y+15;
    wzorek_y[2]=q_y-15;
    wzorek_y[3]=q_y+15;
    wzorek_y[4]=q_y-15;
    wzorek_y[5]=q_y+15;
    wzorek_y[6]=q_y-15;
    wzorek_y[7]=q_y+15;

    body.x = q_x-70;
    body.y = q_y-15; 
    body.w = 140;
    body.h = 30;
    noga_l.x=q_x-40;
    noga_l.y=q_y+15;
    noga_l.w=10;
    noga_l.h=15;
    noga_p.x=q_x+30;
    noga_p.y=q_y+15;
    noga_p.w=10;
    noga_p.h=15;

    pod_smigla_l.x=q_x-50;
    pod_smigla_l.y=q_y-40;
    pod_smigla_l.w=5;
    pod_smigla_l.h=25;
    pod_smigla_p.x=q_x+40;
    pod_smigla_p.y=q_y-40;
    pod_smigla_p.w=5;
    pod_smigla_p.h=25;
    SDL_SetRenderDrawColor(gRenderer.get(), 96,96 ,96 ,255); //body
    SDL_RenderFillRect(gRenderer.get(), &body);
    filledCircleRGBA(gRenderer.get(),body.x,q_y,15,96,96 ,96 ,255);  //body
    filledCircleRGBA(gRenderer.get(),body.x+140,q_y,15,96,96 ,96 ,255); //body
    SDL_SetRenderDrawColor(gRenderer.get(), 64,64 ,64 ,255);
    SDL_RenderFillRect(gRenderer.get(), &noga_l);
    SDL_RenderFillRect(gRenderer.get(), &noga_p);
    SDL_SetRenderDrawColor(gRenderer.get(), 0,0 ,0 ,255);
    SDL_RenderFillRect(gRenderer.get(), &pod_smigla_l);
    SDL_RenderFillRect(gRenderer.get(), &pod_smigla_p);
    //filledCircleRGBA(gRenderer.get(),q_x,q_y,5,0x00, 0x00, 0xFF, 0xFF);
    
   filledPolygonColor(gRenderer.get(),punkty_x,punkty_y, 6, 0xffff0000);
   filledPolygonColor(gRenderer.get(),punkty_x1,punkty_y, 6, 0xffff0000);
   filledPolygonRGBA(gRenderer.get(),wzorek_x,wzorek_y, 8,128,128,128,255); //wzorek
    //do tego momentu
    SDL_SetRenderTarget(gRenderer.get(),nullptr);
    SDL_Point center;
    center.x=q_x;
    center.y=q_y;
    SDL_RenderCopyEx(gRenderer.get(),texture,NULL,NULL,-q_theta*57.2957795,&center,SDL_FLIP_NONE);

    SDL_DestroyTexture(texture);
}
