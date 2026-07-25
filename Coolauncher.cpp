#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<vector>
#include<cstdlib>
#include<windows.h>
#include<nlohmann\json.hpp>
using json = nlohmann::json;
namespace fs = std::filesystem;
int slide;
int cursor = 1;
int max_cursor;
bool keycheck = true;
json settings;
json profile_conf;
std::vector<std::string> profile;
std::vector<std::string> profile_file;

void input(){
    if(slide == 2){
        std::string username;
        std::cin >> username;
        settings["username"] = username;
    }else if(slide == 4){
        Sleep(200);
        std::string directory;
        std::cin >> directory;
        settings["directory"] = directory;
    }else if(slide == 10){
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        bool check_input = true;
        std::cout << "Name: ";
        std::string name;
        while(check_input){std::getline(std::cin, name); if(name.empty()){std::cout << "Pleas eneter name!!!\n"; std::cout << "Name: ";}else{check_input = false;}}
        std::cout << std::endl;
        std::cout << std::endl;
        profile_conf["profile_name"] = name;
        std::cout << "Minecraft version: ";
        std::string version;
        check_input = true;
        while(check_input){std::getline(std::cin, version); if(version.empty()){std::cout << "Pleas eneter version!!!\n"; std::cout << "Minecraft version: ";}else{check_input = false;}}
        std::cout << std::endl;
        std::cout << std::endl;
        profile_conf["minecraft_version"] = version;
        std::cout << "Minecraft directory: ";
        std::string minecraft_directory;
        std::getline(std::cin, minecraft_directory);
        if(minecraft_directory.empty()){
            profile_conf["minecraft_directory"] = settings["directory"].get<std::string>();
        }else{
            profile_conf["minecraft_directory"] = minecraft_directory;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Java diretcory: ";
        std::string java_directory;
        std::getline(std::cin, java_directory);
        if(java_directory.empty()){
            profile_conf["java_directory"] = "java";
        }else{
            profile_conf["java_directory"] = java_directory;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "JVM arguments: ";
        std::string jvm_arguments;
        std::getline(std::cin, jvm_arguments);
        if(jvm_arguments.empty()){
            profile_conf["jvm_arguments"] = "non";
        }else{
            profile_conf["jvm_arguments"] = jvm_arguments;
        }
        std::cout << std::endl;
    }else if(slide == 12){
        std::cout << "Enter username: ";
        std::string username;
        std::cin >> username;
        std::cout << std::endl;
        settings["username"] = username;
    }else if(slide == 14){
        std::cout << "Enter minecraft directory: ";
        std::string directory;
        std::cin >> directory;
        std::cout << std::endl;
        settings["directory"] = directory;
    }
}

void updConsole(){
    system("cls");
    if(slide == 1){
        std::cout << "Welcome to the initial setup settings for Coolauncher!\n";
        std::cout << "==============================\n";
        std::cout << "Press Enter to start setup!\n";
    }else if(slide == 2){
        std::cout << "Coolauncher setup settings\n";
        std::cout << "==============================\n";
        std::cout << std::endl;
        std::cout << "Enter username: ";
        input();
        slide = 3;
        updConsole();
    }else if(slide == 3){
        std::cout << "Coolauncher setup settings\n";
        std::cout << "==============================\n";
        std::cout << "Choose minecraft directory\n";
        if(cursor == 1){std::cout << "> "; std::cout << "Default directory\n";}else{std::cout << "  Default directory\n";}
        if(cursor == 2){std::cout << "> "; std::cout << "Custom directory\n";}else{std::cout << "  Custom directory\n";}
        max_cursor = 2;
    }else if(slide == 4){
        std::cout << "Coolauncher setup settings\n";
        std::cout << "==============================\n";
        std::cout << std::endl;
        std::cout << "Minecraft directory: ";
        input();
        slide = 5;
        updConsole();
    }else if(slide == 5){
        std::cout << "Coolauncher finish setup settings\n";
        std::cout << "==============================\n";
        std::cout << std::endl;
        std::cout << "Press Enter to finish!\n";
    }else if(slide == 6){
        std::cout << "Coolauncher\n";
        std::cout << "==============================\n";
        if(cursor == 1){std::cout << "> "; std::cout << "Start my favourite profile minecraft\n";}else{std::cout << "  Start my favourite profile minecraft\n";}
        if(cursor == 2){std::cout << "> "; std::cout << "Profiles\n";}else{std::cout << "  Profiles\n";}
        if(cursor == 3){std::cout << "> "; std::cout << "Settings\n";}else{std::cout << "  Settings\n";}
        max_cursor = 3;
    }else if(slide == 7){
        std::cout << "Start minecraft\n";
        std::cout << "==============================\n";
        std::cout << "Minecraft started version: " << profile_conf["minecraft_version"].get<std::string>() << std::endl;
    }else if(slide == 8){
        std::cout << "Coolauncher minecraft profiles\n";
        std::cout << "==============================\n";
        if(cursor == 1){std::cout << "> "; std::cout << "Create minecraft profile\n";}else{std::cout << "  Create minecraft profile\n";}
        if(profile.empty()){
            std::cout << "      Profile not found\n";
            max_cursor = 1;
        }else{
            for(size_t number = 0; number < profile.size(); number = number + 1){
                if(cursor == static_cast<int>(number) + 2){std::cout << "> "; std::cout << profile[number]; std::cout << std::endl;}else{std::cout << "  "; std::cout << profile[number]; std::cout << std::endl;}
            }
            max_cursor = static_cast<int>(profile.size()) + 1;
        }
    }else if(slide == 9){
        std::cout << "Coolauncher settings\n";
        std::cout << "==============================\n";
        if(cursor == 1){std::cout << "> "; std::cout << "Username\n";}else{std::cout << "  Username\n";}
        if(cursor == 2){std::cout << "> "; std::cout << "Minecraft directory\n";}else{std::cout << "  Minecraft directory\n";}
        if(settings["favourite"].get<std::string>() != "non"){
            if(cursor == 3){std::cout << "> "; std::cout << "Reset favourite profile\n";}else{std::cout << "  Reset favourite profile\n";}
            if(cursor == 4){std::cout << "> "; std::cout << "Exit\n";}else{std::cout << "  Exit\n";}
            max_cursor = 4;
        }else{
            if(cursor == 3){std::cout << "> "; std::cout << "Exit\n";}else{std::cout << "  Exit\n";}
            max_cursor = 3;
        }
    }else if(slide == 10){
        std::cout << "Coolauncher ctreate profile\n";
        std::cout << "==============================\n";
        input();
    }else if(slide == 11){
        std::cout << "Username settings\n";
        std::cout << "==============================\n";
        std::cout << "Username: " << settings["username"] << std::endl;
        if(cursor == 1){std::cout << "> "; std::cout << "Change\n";}else{std::cout << "  Change\n";}
        if(cursor == 2){std::cout << "> "; std::cout << "Exit\n";}else{std::cout << "  Exit\n";}
        max_cursor = 2;
    }else if(slide == 12){
        std::cout << "Username settings\n";
        std::cout << "==============================\n";
        input();
        slide = 9;
        updConsole();
    }else if(slide == 13){
        std::cout << "Minecraft directory settings\n";
        std::cout << "==============================\n";
        std::cout << "Minecraft directory: " << settings["directory"] << std::endl;
        if(cursor == 1){std::cout << "> "; std::cout << "Change\n";}else{std::cout << "  Change\n";}
        if(cursor == 2){std::cout << "> "; std::cout << "Exit\n";}else{std::cout << "  Exit\n";}
        max_cursor = 2;
    }else if(slide == 14){
        std::cout << "Minecraft directory settings\n";
        std::cout << "==============================\n";
        input();
        slide = 9;
        updConsole();
    }else if(slide == 15){
        std::cout << "Choose favourite minecraft profile\n";
        std::cout << "==============================\n";
        if(!profile.empty()){
            for(size_t number = 0; number < profile.size(); number = number + 1){
                if(cursor == static_cast<int>(number) + 1){std::cout << "> "; std::cout << profile[number]; std::cout << std::endl;}else{std::cout << "  "; std::cout << profile[number]; std::cout << std::endl;}
            }
            if(cursor == static_cast<int>(profile.size()) + 1){std::cout << "> "; std::cout << "Cancel\n";}else{std::cout << "  "; std::cout << "Cancel\n";}
            max_cursor = static_cast<int>(profile.size()) + 1;
        }else{
            std::cout << "      Profile not faund\n";
            std::cout << "      Press Enter to exit\n";
        }
    }
}

void scan_profiles(){
    profile.clear();
    profile_file.clear();
    if(fs::exists("profiles") && fs::is_directory("profiles")){
        for(const auto& entry : fs::directory_iterator("profiles")){
            if(entry.is_regular_file() && entry.path().extension() == ".json"){
                profile_file.push_back(entry.path().string());
                std::ifstream profile_file_read(entry.path().string());
                if(profile_file_read.is_open()){
                    profile_conf.clear();
                    profile_file_read >> profile_conf;
                    std::string name = profile_conf["profile_name"].get<std::string>();
                    profile.push_back(name);
                }
            }
        }
    }
}

void create_profile(){
    std::string file_name = profile_conf["profile_name"].get<std::string>() + ".json";
    std::string file = "profiles/" + file_name;
    std::ofstream profile_file_conf(file);
    if(profile_file_conf.is_open()){
        profile_file_conf << profile_conf.dump(4);
        profile_file_conf.close();
    }
}

void check_default_minecraft_directory(){
    char* appdata_rouming_directory = std::getenv("APPDATA");
    if(appdata_rouming_directory){
        fs::path game_directory = fs::path(appdata_rouming_directory) / ".minecraft";
        if(!fs::exists(game_directory)){
            fs::create_directory(game_directory);
        }
        settings["directory"] = game_directory.string();
    }else{
        settings["directory"] = "minecraft";
        fs::create_directory("minecraft");
    }
}

void start_minecraft(int index_profile){
    std::ifstream minecraft(profile_file[index_profile]);
    if(minecraft.is_open()){
        minecraft >> profile_conf;
        minecraft.close();
        std::string command = "bin\\python\\python.exe bin\\launch_minecraft\\launch_minecraft.py " + profile_conf["minecraft_version"].get<std::string>() + " \"" + profile_conf["minecraft_directory"].get<std::string>() + "\" \"" + profile_conf["java_directory"].get<std::string>() + "\" \"" + profile_conf["jvm_arguments"].get<std::string>() + "\" " + settings["username"].get<std::string>();
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        CreateProcessA(NULL, command.data(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        slide = 7;
        updConsole();
        Sleep(2000);
    }
}

void add_favourite_profile(int index_profile_file){
    settings["favourite"] = profile_file[index_profile_file];
    std::ofstream favourite("settings.json");
    if(favourite.is_open()){
        favourite << settings.dump(4);
        favourite.close();
    }
}

void start_favourite(){
    if(settings["favourite"] == "non"){
        slide = 15;
        updConsole();
    }else{
        std::ifstream minecraft(settings["favourite"].get<std::string>());
        if(minecraft.is_open()){
            minecraft >> profile_conf;
            minecraft.close();
            std::string command = "bin\\python\\python.exe bin\\launch_minecraft\\launch_minecraft.py " + profile_conf["minecraft_version"].get<std::string>() + " \"" + profile_conf["minecraft_directory"].get<std::string>() + "\" \"" + profile_conf["java_directory"].get<std::string>() + "\" \"" + profile_conf["jvm_arguments"].get<std::string>() + "\" " + settings["username"].get<std::string>();
            STARTUPINFOA si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));
            CreateProcessA(NULL, command.data(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            slide = 7;
            updConsole();
        }
    }
}

void save_settings(bool reset_favourite = false){
    std::ofstream save_settings("settings.json");
    if(reset_favourite == true){settings["favourite"] = "non";}
    if(save_settings.is_open()){
        save_settings << settings.dump(4);
        save_settings.close();
    }
}

void enter(){
    if(slide == 1){
        slide = 2;
        updConsole();
    }else if(slide == 3){
        if(cursor == 1){slide = 5; cursor = 1; updConsole(); check_default_minecraft_directory();}
        if(cursor == 2){slide = 4; cursor = 1; updConsole();}
    }else if(slide == 5){
        slide = 6;
        cursor = 1;
        save_settings(true);
        updConsole();
    }else if(slide == 6){
        if(cursor == 1){if(settings["favourite"].get<std::string>() == "non"){scan_profiles(); start_favourite(); cursor = 1;}else{start_favourite(); keycheck = false;}}
        if(cursor == 2){slide = 8; cursor = 1; scan_profiles(); updConsole();}
        if(cursor == 3){slide = 9; cursor = 1; updConsole();}
    }else if(slide == 8){
        if(cursor == 1){
            slide = 10;
            updConsole();
            create_profile();
            scan_profiles();
            slide = 8;
            updConsole();
        }else{
            if(!profile.empty()){
                int index = cursor - 2;
                start_minecraft(index);
                keycheck = false;
            } 
        }
    }else if(slide == 9){
        if(cursor == 1){slide = 11; cursor = 1; updConsole();}
        if(cursor == 2){slide = 13; cursor = 1; updConsole();}
        if(settings["favourite"].get<std::string>() != "non"){if(cursor == 3){save_settings(true); std::cout << std::endl; std::cout << "Favourite profile is reseted!";}if(cursor == 4){slide = 6; cursor = 1; updConsole();}}else{if(cursor == 3){slide = 6; cursor = 1; updConsole();}}
    }else if(slide == 11){
        if(cursor == 1){slide = 12; cursor = 1; updConsole(); save_settings();}
        if(cursor == 2){slide = 9; cursor = 1; updConsole();}
    }else if(slide == 13){
        if(cursor == 1){slide = 14; cursor = 1; updConsole(); save_settings();}
        if(cursor == 2){slide = 9; cursor = 1; updConsole();}
    }else if(slide == 15){
        if(!profile.empty()){
            if(cursor == static_cast<int>(profile.size()) + 1){
                slide = 6;
                updConsole();
            }else{
                int index = cursor - 1;
                add_favourite_profile(index);
                slide = 6;
                updConsole();
                cursor = 1;
            }
        }else{
            slide = 6;
            updConsole();
        }
    }

    cursor = 1;
    Sleep(100);
}

void import_settings(){
    std::ifstream import_settings_file("settings.json");
    if(import_settings_file.is_open()){
        import_settings_file >> settings;
        import_settings_file.close();
        slide = 6;
        updConsole();
    }else{
        slide = 1;
        updConsole();
    }
}

int main(){
    import_settings();
    while(keycheck){
        if(GetAsyncKeyState(VK_UP) & 0x8000){if(cursor > 1){cursor = cursor - 1; updConsole();}}
        if(GetAsyncKeyState(VK_DOWN) & 0x8000){if(cursor < max_cursor){cursor = cursor + 1; updConsole();}}
        if(GetAsyncKeyState(VK_RETURN) & 0x8000){enter();}

        Sleep(65);
    }
}