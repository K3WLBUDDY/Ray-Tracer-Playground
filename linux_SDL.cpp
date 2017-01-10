#include<iostream>
#include<stdlib.h>
#include<SDL2/SDL.h>

int main(int argc, char** argv)
{
  char cx;
  std::cout<<"\n\n SDL Window in Linux!";
  
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* sWindow= NULL;

  sWindow = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366,768, SDL_WINDOW_OPENGL);

  std::cout<<"\n Press any Key to Quit!";
  std::cin>>cx;
  
  return 0;
  
}
