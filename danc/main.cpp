//
//  main.cpp
//  danc
//
//  Created by Daniel  Fernandez on 2/6/20.
//  Copyright © 2020 Daniel  Fernandez. All rights reserved.
//
/*
 --------DOCUMENTATION---------
 
 Arguments:
1st: command
 
 ------END DOCUMENTATION-------
 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::__fs::filesystem;

struct Dic {
    string key;
    string value;
};

//tools
void makeDir(string name);
//end tools

void runProject(string projectName);
void startProject(string projectName);
void deleteProject(string projectName);
void buildProject(string projectName);
void zipProject(string projectName);
void unzipProject(string projectName);

void startTemplate(string templateName);
void makeTemplate(string templateName);
void installTemplate(string templateName);

int main(int argc, const char * argv[]) {

    if(argc <= 1) {
        cout << "Missing arguments" << endl;
        return 0;
        
    } else {
        //start here
        for (int i = 1; i < argc; i++) {
            
            //startproject
            if(strcmp(argv[i], "startproject") == 0) {
                if (i < argc - 1) {
                    startProject(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end start project
            
            //deleteproject
             else if(strcmp(argv[i], "deleteproject") == 0) {
                if (i < argc - 1) {
                    deleteProject(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end deleteproject
            
            //starttemplate
            else if(strcmp(argv[i], "starttemplate") == 0) {
                if (i < argc - 1) {
                    startTemplate(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end starttemplate
            
            //maketemplate
            else if(strcmp(argv[i], "maketemplate") == 0) {
                if (i < argc - 1) {
                    makeTemplate(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end maketemplate
            
            //installtemplate
            else if(strcmp(argv[i], "installtemplate") == 0) {
                if (i < argc - 1) {
                    installTemplate(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end installtemplate
            
            //compile
            else if(strcmp(argv[i], "build") == 0) {
                if (i < argc - 1) {
                    buildProject(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end compile
            
            //run
            else if(strcmp(argv[i], "run") == 0) {
                if (i < argc - 1) {
                    runProject(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end run
            
            //brun
            else if(strcmp(argv[i], "brun") == 0) {
                if (i < argc - 1) {
                    buildProject(argv[++i]);
                    runProject(argv[i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end brun
            
            //zip
            else if(strcmp(argv[i], "zip") == 0) {
                if (i < argc - 1) {
                    zipProject(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end zip
            
            //unzip
            else if(strcmp(argv[i], "unzip") == 0) {
                if (i < argc - 1) {
                    unzipProject(argv[++i]);
                } else {
                    cout << "Missing project name" << endl;
                }
            }
            //end unzip
            
            else {
                cout << "Invalid command" << endl;
            }
        }
    }
}

void startProject(string projectName) {
    makeDir(projectName);
    
    //project file
    string main_f_path = projectName + "/" + projectName + ".dan";
    ofstream data_f(main_f_path);
    data_f << "#zip file extension" << endl;
    data_f << "#this option allows you to " << endl;
    data_f << "#customize the zip file name " << endl;
    data_f << "danc" << endl;
    data_f.close();
    
    //main config
    string project_f_path = projectName + "/" + projectName + ".cpp";
    data_f.open(project_f_path);
    data_f << "// DANC PROJECT" << endl;
    data_f << "// Project name: " << projectName << endl;
    data_f << "//\n// File: main.cpp" << endl;
    data_f << "//\n" << endl;
    data_f << "#include <iostream>\n"
            << "\nint main() {\n"
            << "    std::cout << \"HelloWorld!\" << std::endl;\n"
            << "    return 0;\n"
            << "}" << endl;
    data_f.close();
}
void buildProject(string projectName) {
    string cmd = "g++ -o " + projectName + "/" + projectName + " " + projectName + "/" + projectName + ".cpp";
    system(cmd.c_str());
}
void runProject(string projectName) {
    string cmd = "./" + projectName + "/" + projectName;
    system(cmd.c_str());
}
void deleteProject(string projectName) {
    string cmd = "rm -rf " + projectName;
    system(cmd.c_str());
}
void zipProject(string projectName) {
    string zipName = projectName;
    ifstream data(projectName + "/" + projectName + ".dan");
    if(data) {
        string input;
        
        int option = 0;
        
        while(getline(data, input)) {
            if(input[0] != '#') {
                switch (option) {
                    case 0:
                        //zip name extra
                        zipName += ("-" + input);
                        break;
                }
                option++;
            }
                
        }
        
        data.close();
    }
    string cmd = "zip -r " + zipName + ".zip " + projectName;
    system(cmd.c_str());
}
void unzipProject(string projectName) {
    string cmd = "unzip " + projectName + ".zip ";
    system(cmd.c_str());
}

void startTemplate(string templateName) {
    startProject(templateName);
    
    string template_f_path = templateName + "/" + templateName + ".cfg";
    ofstream template_f(template_f_path);
    
    template_f << "%NAME% Enter your name" << endl;
    
    template_f.close();
    
}
void makeTemplate(string templateName) {
    string cmd = "zip -r " + templateName + ".dantmp " + templateName;
    system(cmd.c_str());
}
void installTemplate(string templateName) {
    ifstream test(templateName + ".dantmp");
    if(!test)
        return;
    test.close();
    
    string cmd = "unzip -j -d " + templateName + " " + templateName + ".dantmp";
    system(cmd.c_str());
    
    ifstream data(templateName + "/" + templateName + ".cfg");
    if(data) {
        Dic input;
        vector<Dic> elements;
        
        while (data >> input.key) {
            
            string cmd;
            
            if (input.key[0] == '%' && input.key[input.key.length() - 1] == '%') {
            
                getline(data, cmd);
                cout << cmd << ": ";
                cin >> input.value;
                cin.clear();
                cin.ignore(10, '\n');
                elements.push_back(input);
                
            } else {
                getline(data, cmd);
            }
        }
        
        data.close();
        
        //find tags and substitute
        for (const auto & entry : fs::directory_iterator(templateName + "/")) {
            if (entry.path() != (templateName + "/" + templateName + ".cfg")) {
                
                string file = "";
                string input;
                ifstream data(entry.path());
                
                while(getline(data, input)) {
                    for(Dic &d : elements) {
                        size_t found = input.find(d.key);
                        while(found != string::npos) {
                            input.replace(found, d.key.length(), d.value);
                            found = input.find(d.key);
                        }
                        
                    }
                    file += (input + '\n');
                }
                data.close();
                
                ofstream data_o(entry.path());
                data_o << file;
                data_o.close();
            }
            
        }
        
        string cmd = "rm " + templateName + "/" + templateName + ".cfg";
        system(cmd.c_str());
    }
    
    
}

//tools
void makeDir(string name) {
    string cmd = "mkdir " + name;
    system(cmd.c_str());
}
//end tools
