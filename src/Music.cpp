#include "../include/Music.h"
#include "../include/Resources.h"

Music::Music(){//seta music como nullptr (música não carregada)
  music = nullptr;
}

Music::Music(std::string file){//seta music como nullptr e em seguida chama Open para abrir uma música
  music = nullptr;
  Open(file);
}

void Music::Play(int times, float ms){//executa a música (times) vezes, times = -1 indica para tocar a música infinitamente
  if (music != nullptr){
    if (Mix_FadeInMusic(music.get(), times, ms) == -1) {//exxecuta a música, mas se o retorno for -1, há um erro
      std::cout << "Can't play music file: " << SDL_GetError()  << std::endl;
    }
  }
  else {
    std::cout << "no music loaded" << std::endl;
  }
}

void Music::Stop(int msToStop){//para a música
  Mix_FadeOutMusic(msToStop);//para a música atual dando um efeito de fade, isto é, diminuindo gradualmente o volume até chegar em 0.
}

void Music::Open(std::string file){
  // const char* MusicFile = file.c_str();//converte a string do caminho para const char* que é usado pela função
  // music = Mix_LoadMUS(MusicFile);//carrega a música indicada pelo caminho em file
  music = Resources::GetMusic(file);
  if (music == nullptr){
    std::cout << "Can't open, music file null: " << SDL_GetError()  << std::endl;
  }
}

bool Music::IsOpen(){//checa se a música é nula
  if (music == nullptr) {
    return false;
  }
  else {
    return true;
  }
}

Music::~Music(){//destrutor, chama stop e libera a música da memória
 Stop(0);//passando 0 pra a função Mix_FadeOutMusic em Stop, a música para instantaneamente
}
