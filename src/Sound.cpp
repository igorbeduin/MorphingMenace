#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound(GameObject& associated):Component(associated){
  Component::associated = associated;
  chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file):Component(associated){
  Open(file);
}

Sound::~Sound(){
}

void Sound::Play(int times){
  if (chunk != nullptr) {
    channel = Mix_PlayChannel(EMPTY_CHANNEL, chunk.get(), times -1); //empty_channel = -1 a função escolherá o primeiro canal vazio e retornará o número dele
                                                              // loops indica quantas vezes o som deve ser repetido, ou seja, loops = 1 faz tocar duas vezes.
  } else {
    std::cout << "Chunk null, can't play sound, Error code: "<< SDL_GetError() << std::endl;
  }
}

void Sound::Stop(){
  if (chunk != nullptr) {
    Mix_HaltChannel(channel);//para a música no canal dado
  } else {
    std::cout << "Chunk null, no sound to stop, Error code: "<< SDL_GetError() << std::endl;
  }
}

void Sound::Open(std::string file){
  // const char* path = file.c_str();
  // chunk =  Mix_LoadWAV(path);
  chunk = Resources::GetSound(file); // Chama a GetSounds para alocar o som caso ele seja novo ou pegar da tabela o som já existente
  if (chunk == nullptr) {
    std::cout << "Error getting sound, Error code: "<< SDL_GetError() << std::endl;
  }
}

bool Sound::IsOpen(){
  if (chunk == nullptr) {
    return false;
  }
  else {
    return true;
  }
}

void Sound::Update(float dt){
}

void Sound::Render(){
}

bool Sound::Is(std::string type){
  return (type == "Sound");
}
