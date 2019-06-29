#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

//inicialização de membro estático da classe
Game *Game::instance = nullptr;

Game::Game (std::string title, int width, int height){

  int SDLError, ImgError, MixError, TxtError;
  dt = 0;
  frameStart = 0;

  if (Game::instance != nullptr){//chechando se já existe uma instância do jogo rodando, se tiver existe um problema na lógica
    std::cout << "Game Logic Problem" << std::endl;
  }
  else{
    Game::instance = this;//se não houver uma instância do jogo rodando, recebe this
  }


  SDLError = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);//SDL_INIT retorna diferente de zero quando falaha
  if (SDLError != 0){//caso falhe, deve-se abortar e mostrar uma mensagem de erro
    std::cout << "SDL_Init failed, Error Code: " << SDL_GetError() << std::endl;//sdl_get error obtem o ultimo erro ocorrido na biblioteca
  }
  else {//casso não haja falha, inicia a imagem
    // std::cout << "SDL initiated" << std::endl;
    ImgError = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG |IMG_INIT_TIF);//img_init carregar os loaders da imagem, e retorna um bitmask correspondente aos loaders que ela conseguiu carregar
    if (ImgError == 0) {//se não carrefar nenhum, o retorno é 0 e há um erro
      std::cout << "IMIG_Init failed to load" << std::endl;
    }
    else {//conseguindo iniciar as imagens, inicializa-se a música, que funciona de forma semelhante à imagem.
      // std::cout << "Image initiated" << std::endl;
      MixError = Mix_Init( MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG); //mix_init carregar os loaders das músicas, e retorna um bitmask correspondente aos loaders que ela conseguiu carregar
      if (MixError == 0){//se não carregar nenhum loadoer, o retorno é 0 e há um erro
        std::cout << "MIX_Init failed to load" << std::endl;
      }
      else{//channels é a quantidade de canais de saída de áudio (default = 2), formtat é o formato da amostra baseado no suporte de audio do SDL, Frequency é a frequência do som, e chuncksize são os bytes usados por amostra
        // std::cout << "Mix initiated" << std::endl;
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHUNKSIZE);
        Mix_AllocateChannels(AUDIO_CHANNELS);//aloca os canais de áudio usados pelo jogo

        const char* Window_title = title.c_str();//converte o valor dado em string para cons char*
        SDL_Window* window = SDL_CreateWindow(Window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);//cria a janela em que o jogo vai ser executado
        if (window == nullptr) {//as entradas de create wndow passam o nome da janela, a posição dela na tela (a flag centraliza), tamanho da tela (width e height) e uma flag para padrões da janela
        std::cout << "Failed to create window, error code: " << SDL_GetError() << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//cria um renderizador para a janela cirada, como entradas colocamos a janela, um valor de index que determinaqual dos drivers devemos usar;
        //o valor -1 faz o SDL escolher o melhor renderizador para o ambiente e para as flags setadas, o terceiro argumento é a flag
        if (renderer == nullptr) {
          std::cout << "Failed to create render, error code: " << SDL_GetError() << std::endl;
        }
        else{
          TxtError = TTF_Init();
          if (TxtError != 0) {
            std::cout << "TTF_Init failed to load" << std::endl;
          }
          // else{
          //   std::cout << "TTF_INIT LOADED" << std::endl;
          // }
        }
      }
    }
  }
  storedState = nullptr;
  srand(time(NULL));

}

Game& Game::GetInstance(){//cria a instância do jogo
  std::string title = GAME_NAME;
  int width = WINDOW_WIDTH;
  int height = WINDOW_HEIGHT;

  if(Game::instance != nullptr){
    return (*Game::instance);
  }
  else {
    Game::instance = new Game(title, width, height);
    return (*Game::instance);
  }
}

Game::~Game(){//destrutor desfaz as inicializações, deleta o estado, ecerra SDL_Music e SDL_image, destrói o renderizador e a janela e encerra a SDL

  if (storedState != nullptr) {
    delete storedState;
  }

  while(!stateStack.empty()){
    stateStack.pop();
  }

  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
  Resources::ClearFonts();

  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

State& Game::GetCurrentState(){//Retorna o estado atual
  return *(stateStack.top());
}

SDL_Renderer* Game::GetRenderer(){//Retorna o renderer a ser usado
  return renderer;
}

void Game::CalculateDeltaTime(){
  int previousFrame = frameStart;
  frameStart = (float)SDL_GetTicks();
  dt = float(frameStart - previousFrame)/1000;
  // std::cout << "previousFrame: " << previousFrame << " -- frameStart: " << frameStart << " -- dt:  " << dt << '\n';
}

float Game::GetDeltaTime(){
  return dt;
}

void Game::Run(){//loop principal do jogo, será implementado em 4 etapas, porém nesse trabalho apenas as etapas 3 e 4

  InputManager& input = InputManager::GetInstance();
  // state->Start();

  if (storedState == nullptr) {//se não houver um estado inicial, encerra o jogo
    return;
  }
  else{//armazena o estado inicial na pilha e o inicializa
    stateStack.emplace(storedState);
    stateStack.top()->Start();
    storedState = nullptr;//não tem mais estado guardado já que o que estava foi pra pilha
  }


  while(stateStack.top()->QuitRequested() != true && !stateStack.empty()){//enquanto um estado não pediu pra sair e a pilha não estiver vazia

    if (stateStack.top()->PopRequested()) {//
      stateStack.pop();//se um estado pediu pra sair da pilha, pop nele
      Resources::ClearImages();
      Resources::ClearMusics();
      Resources::ClearSounds();
      Resources::ClearFonts();

      if (!stateStack.empty()) {//se a pilha nnão estiver vazia após o pop, retoma o estado no topo
        stateStack.top()->Resume();
      }
    }

    if (storedState != nullptr) {//se tinha algum estado guardado

      if (!stateStack.empty()) {//se a pilha não estava vazia, pausa o estado do topo para inciar o novo (que estava guardado)
        stateStack.top()->Pause();
      }
      // std::cout << "colocou novo state na pilha" << '\n';
      stateStack.emplace(storedState);//armazena o estado guradado na pilha
      stateStack.top()->Start();//inicializa o novo estado no topo
      storedState = nullptr;//nçao tem mais estado guardado
    }
    if (stateStack.empty()) {//se a pilha estiver vazia, sai do loop
      break;
    }
    // std::cout << stateStack.size() << '\n';
    CalculateDeltaTime();
    input.Update();
    stateStack.top()->Update(dt);
    stateStack.top()->Render();
    SDL_RenderPresent(Game::GetInstance().GetRenderer());
    //SDL_Delay(33);//impõe-se um limite de framerate, com um delay de 33ms, nos dará aproximadamente 30 FPS, (usado para não usar 100% di cpu já que é desnecessário)
  }

  while (!stateStack.empty()) {//se a pilha não estava vazia, pausa o estado do topo para inciar o novo (que estava guardado)
    stateStack.pop();
  }
  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
  Resources::ClearFonts();

}

void Game::Push(State* state){
  storedState = state;
}
