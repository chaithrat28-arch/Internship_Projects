#include"header.h"

void html_begin(FILE *html_file)
{
    fprintf(html_file,"<!DOCTYPE html>\n<html>\n<body style='background-color:rgb(34, 33, 33);'>\n<pre>\n");
}

void html_end(FILE *html_file)
{
    fprintf(html_file,"</pre>\n</body>\n</html>\n");
}

void html_body(FILE *html_file,char *word, int key)
{
    if(key == KEYWORD)
    fprintf(html_file,"<span style='color:rgb(55, 75, 226);;'>%s</span>",word);
    // fprintf(html_file,"<span style='color:hsla(225, 90%%, 59%%, 0.66);'>%s</span>",word);
    else if(key == IDENTIFIER )
    fprintf(html_file,"<span style='color:white;'>%s</span>",word);
    else if(key == OPERATOR)
    fprintf(html_file,"<span style='color:white;'>%s</span>",word);
    else if(key == SPECIAL_CHARACTER)
    fprintf(html_file,"<span style='color:rgb(246, 242, 4);'>%s</span>",word);
    else if(key == VALUE)
    fprintf(html_file,"<span style='color:rgb(141, 210, 146);'>%s</span>",word);
    else if(key == COMMENTS)
    fprintf(html_file,"<span style='color:rgb(51, 142, 33);'>%s</span>",word);
    else if(key == STRING_LITERAL)
    fprintf(html_file,"<span style='color:rgba(205, 135, 116, 0.89);'>%s</span>",word);
    else if(key == PRE_PROCESSORS)
    fprintf(html_file,"<span style='color:rgb(198, 53, 203);'>%s</span>",word);
}

int is_keyword(char *buf)
{
    char *keyword[] = {
        "int" , "float" ,"char" , "double" , "long" , "short", "signed" , "unsigned" ,
        "if" , "else", "switch", "case" ,"default" , "break" , "continue", 
        "do" , "for" , "while", "static" ,"volatile" , "const","auto",
        "struct", "union" , "typedef" , "void","sizeof","register","goto","extern","return","enum"
    };

    int n = sizeof(keyword) / sizeof(keyword[0]);

    //compare untill it gets match keyword, if yes means return KEYWORD
    for(int i=0;i<n;i++)
    {
        if(strcmp(buf,keyword[i]) == 0)
        {
            return KEYWORD;
        }
    }
    return IDENTIFIER;
}

int is_operator(char ch)
{
    char operator[] = { '+','-','/','*','%','=','<','>','!','&','|','^', '~'};

    int n = sizeof(operator) / sizeof(operator[0]);

    //compare untill it gets match operator, if yes means return OPERATOR
    for(int i=0;i<n;i++)
    {
        if(ch == operator[i])
        {
            return OPERATOR;
        }
    }

    return 0;
}