#include "../include/Resources.h"

// Inicializa as variáveis estáticas da classe
std::unordered_map<std::string, std::shared_ptr<SDL_Texture> > Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music> > Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> > Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font> > Resources::fontTable;


std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){

     std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::const_iterator it = imageTable.find(file);//procura o arquivo solicitado na tabela de imagens
     SDL_Texture* raw_texture;

     if ( it == imageTable.end() ){//Caso não encontre a imagem, abre e aloca ela na memória

       const char* path = file.c_str();
       raw_texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);
       std::shared_ptr<SDL_Texture> texture(raw_texture, [](SDL_Texture* delete_texture){ SDL_DestroyTexture(delete_texture); } );

       if (texture == nullptr){
           std::cout << "Error loading texture, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
           return nullptr;
       } else {
         imageTable.emplace(file, texture);//coloca a imagem e seu caminho na tabela
         return texture;
       }

     }
       return (it->second);//caso encontre a imagem na tabela retorna seu ponteiro
}


 void Resources::ClearImages(){
   std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::const_iterator it = imageTable.begin();

   while (it != imageTable.end()) {//para todos as imagens na tabela, desaloca a memória e apaga da tabela

     if (it->second.unique()) {
       it = imageTable.erase(it);
     }
     else{
       it++;
     }

   }
   // imageTable.clear();//limpa a tabela
 }


std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){

   std::unordered_map<std::string, std::shared_ptr<Mix_Music> >::const_iterator it = musicTable.find(file);//procura o arquivo solicitado na tabela de Músicas
   if ( it == musicTable.end() ){//Caso não encontre a música, abre e aloca ela na memória

     const char* path = file.c_str();
     Mix_Music* raw_music = Mix_LoadMUS(path);
     std::shared_ptr<Mix_Music> music(raw_music, [](Mix_Music* delete_music){Mix_FreeMusic(delete_music); } );

     if (music == nullptr){
         std::cout << "Error loading music, Error code: "<< SDL_GetError() << std::endl;
     } else {
       musicTable.emplace(file, music);//coloca a música e seu caminho na tabela
       return music;
     }

   }
     return (it->second);//caso encontre a imagem na tabela retorna seu ponteiro
 }

 void Resources::ClearMusics(){
   std::unordered_map<std::string, std::shared_ptr<Mix_Music> >::const_iterator it = musicTable.begin();

   while (it != musicTable.end()) {//para todos as musicas na tabela, desaloca a memória e apaga da tabela
     // Mix_FreeMusic(it->second);
     if (it->second.unique()) {
       it = musicTable.erase(it);
     }
     else{
       it++;
     }
   }
   // musicTable.clear();//limpa a tabela
 }


std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){// Funciona de forma semelhante à GetImage e GetMusic

   std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> >::const_iterator it = soundTable.find(file);
   if ( it == soundTable.end() ){

     const char* path = file.c_str();
     Mix_Chunk* raw_chunk = Mix_LoadWAV(path);
     std::shared_ptr<Mix_Chunk> chunk(raw_chunk, [](Mix_Chunk* delete_chunk){Mix_FreeChunk(delete_chunk); } );

     if (chunk == nullptr){
         std::cout << "Error loading chunk, Error code: "<< SDL_GetError() << std::endl;
     } else {
       soundTable.emplace (file, chunk);
       return chunk;
     }

   }
     return (it->second);
 }

 void Resources::ClearSounds(){// Funciona de forma semelhante à ClearImages e ClearMusics
   std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> >::const_iterator it = soundTable.begin();

   while (it != soundTable.end()) {
     // Mix_FreeChunk(it->second);
     if (it->second.unique()) {
       it = soundTable.erase(it);
     }
     else{
       it++;
     }
   }
   // soundTable.clear();
 }

 std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize){

   std::string file_and_size = file + std::to_string(fontSize);
   std::unordered_map<std::string, std::shared_ptr<TTF_Font> >::const_iterator it = fontTable.find(file_and_size);//procura o arquivo solicitado na tabela de imagens
   TTF_Font* raw_font;

   if ( it == fontTable.end() ){//Caso não encontre a imagem, abre e aloca ela na memória


     const char* path = file.c_str();
    raw_font = TTF_OpenFont(path, fontSize);
    std::shared_ptr<TTF_Font> font(raw_font, [](TTF_Font* delete_font){ TTF_CloseFont(delete_font); } );

    if (font == nullptr){
        std::cout << "Error loading font, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
        return nullptr;
    } else {
      fontTable.emplace(file, font);//coloca a imagem e seu caminho na tabela
      return font;
    }
  }
    return (it->second);//caso encontre a imagem na tabela retorna seu ponteiro
}


  void Resources::ClearFonts(){
    std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::const_iterator it = fontTable.begin();

    while (it != fontTable.end()) {//para todos as imagens na tabela, desaloca a memória e apaga da tabela

      if (it->second.unique()) {
        it = fontTable.erase(it);
      }
      else{
        it++;
      }

    }
    // imageTable.clear();//limpa a tabela
  }
