#include <string>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>


using namespace std;
namespace fs = experimental::filesystem;

string EXPLORER_LOG_PATH = "log.txt";

//Подсчет размера директории
int getDirSize(string dirAddress, double size) {
    for(auto& p: fs::directory_iterator(dirAddress)) {
      //Проверка на то, является ли файл, размер которого мы хотим узнать, директорией
      if(fs::is_directory(p)) {
        fs::path nextDir = p;
        getDirSize(nextDir, size);
      }
      else {
        size = size + file_size(p);
      }
    }
    return size;
}

void displayDir(string dirAddress) {
    //Проверка на существование репозитория
    if(!fs::exists(dirAddress)) {
      throw runtime_error("ERROR: We don't have such directory");
    }
    //Проверка на то, является ли файл директорией
    if(!fs::is_directory(dirAddress)) {
      throw runtime_error("ERROR: Type of file - not directory");
    }
    //Имя директории
    fs::path dirPath = dirAddress;
    fs::path textDir = dirPath.filename();
    //Дата модификации
    auto ftime = fs::last_write_time(dirPath);
    time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

    //Запись данных о директории в файл
    ofstream fout(EXPLORER_LOG_PATH);
    fout << "Directory name: " << textDir << endl;
    fout << "Latest modification: " << asctime(localtime(&cftime)) << endl;
    fout << "Directory size: " << double(getDirSize(dirPath, 0))/1000 << " Kb" << endl;
    fout.close();

}


int main(int argc, char* argv[])
{

  string ad;
  ad = argv[1];
  //ad = "example";

  try {
    displayDir(ad);
  }
  catch(const exception& e) {
    cout << e.what() << endl;
  }
}
