/*******************************************************************************************************
NAME : CHAITHRA T
DATE : 28/02/2026 – 03/02/2026 
PROJECT TITLE : Source to HTML
DESCRIPTION : A Program that reads C source file and generate an HTML file.
PRE-REQUISITE : C programming, file handling, strings, and basic knowledge of HTML.
**********************************************************************************************************/
#include"header.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("ERORR: Invalid Arguments\n");
        printf("USAGE: ./a.out <file_name>\n");
        return 0;
    }

    FILE *src_file, *html_file;
    
    //opening source file in read mode
    src_file = fopen(argv[1],"r");
    if(src_file == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    char html_filename[100];
    //sprintf(html_filename,"%s.html",argv[1]);
    snprintf(html_filename, sizeof(html_filename), "%s.html", argv[1]);
    
    //printf("%s\n",html_filename);

    //if file already exist means delete that file
    remove(html_filename);

    //opening html file in write mode
    html_file = fopen(html_filename,"w");
    if(html_file == NULL)
    {
        printf("Unable to create html file\n");
        return 0;
    }

    //writing HTML begin part in file
    html_begin(html_file);

    char buff[300],ch;
    int i=0;

    //read character till EOF
    while( (ch = fgetc(src_file)) != EOF)
    {
        //printf("[%c]\n", ch);

        //if white space occured write to html_file
        if (isspace(ch))
        {
            fputc(ch, html_file);
            continue;
        }

        //pre-processor directives
        else if(ch =='#')
        {
            i = 0;
            buff[i++] = ch;
            while((ch = fgetc(src_file)) != EOF)
            {
                if(ch == '<')
                {
                    buff[i++] = '&';
                    buff[i++] = 'l';
                    buff[i++] = 't';
                }
                
                //why?? bcz < and  > are predefned characters in html,like formatted code
                else if(ch == '>')
                {
                    buff[i++] = '&';
                    buff[i++] = 'g';
                    buff[i++] = 't';
                }
                
                else if(ch == '\n')
                {
                    break;
                }
                else
                buff[i++] = ch;
            }
            buff[i] = '\0';
            
            //printf("%s\n",buff);
            
            html_body(html_file,buff,PRE_PROCESSORS);

            fputc('\n', html_file);
        }
        
        //keyword and identifier
        else if(isalpha(ch) || ch == '_')
        {
            i = 0;
            buff[i++] = ch;
            while((isalnum(ch = fgetc(src_file))) || ch == '_')
            {
                buff[i++] = ch;
            }

            buff[i] = '\0';

            ungetc(ch, src_file);

            if(is_keyword(buff) == KEYWORD)
            {
                html_body(html_file,buff,KEYWORD);
            }
            else
            {
                html_body(html_file,buff,IDENTIFIER);
            }
        }

        //string literal
        else if (ch == '"')
        {
            char buff1[500];
            int i1 = 0;
            buff1[i1++] = '"';
            while ((ch = fgetc(src_file)) != '"' && ch != EOF)
            {
                if (ch == '\\')
                {
                    buff1[i1++] = ch;
                    ch = fgetc(src_file);
                }

                buff1[i1++] = ch;
            }
            buff1[i1++] = '"';
            buff1[i1] = '\0';
            html_body(html_file,buff1,STRING_LITERAL);
        }

        //special characters
        else if(ch == '{' || ch == '}' || ch == ')' || ch == '(' || ch == '[' || ch == ']' || ch == ';' || ch ==',')
        {
            i = 0;
            buff[i++] = ch;
            buff[i] = '\0';
            html_body(html_file,buff,SPECIAL_CHARACTER);
        }
        //constant values
        else if(isdigit(ch))
        {
            i = 0;
            buff[i++] = ch;

            while(isdigit(ch = fgetc(src_file)) || ch == '.')
            {   
                buff[i++] = ch;
            }

            buff[i] ='\0';

            ungetc(ch,src_file);

            html_body(html_file,buff,VALUE);
        }

        //single and multi line comments
        else if (ch == '/')
        {
            char next = fgetc(src_file);

            if(next == '/')
            {
                i = 0;
                buff[i++] = '/';
                buff[i++] = '/';

                while((ch = fgetc(src_file)) != '\n' && ch != EOF)
                {
                    buff[i++] = ch;
                }

                buff[i] = '\0';

                html_body(html_file,buff,COMMENTS);
                fputc('\n', html_file);
            }
            else if(next == '*')
            {
                i = 0;
                buff[i++] = '/';
                buff[i++] = '*';

                while((ch = fgetc(src_file)) != EOF)
                {
                    buff[i++] = ch;

                    if(ch == '*')
                    {
                        char next2 = fgetc(src_file);
                        if(next2 == '/')
                        {
                            buff[i++] = '/';
                            break;
                        }
                        else
                        {
                            ungetc(next2, src_file);
                        }
                    }
                }

                buff[i] = '\0';
                html_body(html_file,buff,COMMENTS);
            }
        }
        //operators
        else
        {
            i = 0;
            if(is_operator(ch))
            {
                buff[i++] = ch;
                buff[i] = '\0';
                html_body(html_file,buff,OPERATOR);
            }
            //ungetc(ch, src_file);
        }

    }
    
    //html end code
    html_end(html_file);

    printf("Generated HTML file name is %s\n",html_filename);

    return 0;
}

