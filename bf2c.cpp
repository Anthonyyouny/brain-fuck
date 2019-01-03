//brinfuck to C
#include <fstream>
#include <string>

using namespace std;
const int max_box_size = 3000;

/*
 > ָ���һ
 < ָ���һ
 + ָ��ָ����ֽڵ�ֵ��һ
 - ָ��ָ����ֽڵ�ֵ��һ
. ��ASCII�����ָ��ָ���ֽ�����
, ��ASCII���������ݵ�ָ��ָ���ֽ�
[ ���ָ��ָ��ĵ�ԪֵΪ�㣬�����ת����Ӧ��]ָ��Ĵ�һָ�
] ���ָ��ָ��ĵ�Ԫֵ��Ϊ�㣬��ǰ��ת����Ӧ��[ָ��Ĵ�һָ�

*/

ifstream fin;
ofstream fout;
void translate_to_c(const char* file_name);
void retract(int n);


int main(int argc,char ** argv)
{
    for(int i=1;i<argc;i++)
        translate_to_c(argv[i]);
    return 0;
}
void translate_to_c(const char* file_name){
    fin.open(file_name);
    string target_file_name = file_name ;
    target_file_name +=  ".c";
    fout.open(target_file_name.data());
    fout << "//file name: "<<target_file_name<<endl;
    fout << "//this is a c src interpreted from bf src"<<endl;
    fout << "#include <stdio.h>"<<endl;
    fout << "#define MAX_BOX_SIZE " << max_box_size << endl;
    fout << "char box[MAX_BOX_SIZE];" << endl;
    fout << "char *ptr = box;"  << endl;
    fout << "int main(){" << endl;

    char ch;
    while(fin.get(ch)){
        switch(ch){
            case '>':fout << "++ptr;" << endl;break;
            case '<':fout << "--ptr;" << endl;break;
            case '+':fout << "++*ptr;" << endl;break;
            case '-':fout << "--*ptr;" << endl;break;
            case '.':fout << "putchar(*ptr);" << endl;break;
            case ',':fout << "*ptr=getchar();" << endl;break;
            case '[':fout << "while(*ptr){" << endl; break;
            case ']':fout << "}" << endl; break;
        }
    }
    fout << "}" <<endl;
    fin.close();
    fout.close();
}
