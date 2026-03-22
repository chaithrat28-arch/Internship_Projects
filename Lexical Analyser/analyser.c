#include"analyser.h"

//check for keyword or identifier
int is_keyword(char *buf)
{
    //store all keywords in array of pointer consists of string
    char *keyword[] = {
        "int" , "float" ,"char" , "double" , "long" , "short", "signed" , "unsigned" ,
        "if" , "else", "switch", "case" ,"default" , "break" , "continue", 
        "do" , "for" , "while", "static" ,"volatile" , "const","auto",
        "struct", "union" , "typedef" , "void","sizeof","register","goto","extern","return","enum"
    };

    int n = sizeof(keyword) / sizeof(keyword[0]);

    //compare untill it gets match keyword, if yes means return 1 to main
    for(int i=0;i<n;i++)
    {
        if(strcmp(buf,keyword[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//chcek for OPERATORS
int is_operator(char ch)
{
    //store operators in character array
    char operator[] = { '+','-','/','*','%','=','<','>','!','&','|','^', '~'};

    int n = sizeof(operator) / sizeof(operator[0]);

    //compare untill it gets match operator, if yes means return 1 to main
    for(int i=0;i<n;i++)
    {
        if(ch == operator[i])
        {
            return 1;
        }
    }

    return 0;
}

//to handler header
void handle_header(FILE *fp)
{
    int i = 0;
    char header[100],ch;
    header[i++] = '#';
            
    //read character till new line or EOF
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
    {
        header[i++] = ch;
    }

    header[i] = '\0';

    printf("HEADER  : %s\n",header);
}

//to handle strings
void handle_string(FILE *fp)
{
    char buff[250];
    int i=0;
    char ch;

    //read character untill "
    while((ch=fgetc(fp))!='"' && ch!=EOF)
    {
        if(ch=='\\')
        {
            buff[i++]=ch;
            ch=fgetc(fp);
        }
        buff[i++]=ch;
    }

    buff[i]='\0';

    printf("STRING LITERAL : %s\n",buff);
}

//to handle comments
void handle_comment(FILE *fp)
{
    char buff[250];
    int i=0;
    buff[i++] = '/';
    char next = fgetc(fp);
    buff[i++] = next;
    char ch;

    // check single line comment '//'
    if(next=='/')
    {
        while((ch=fgetc(fp))!='\n' && ch!=EOF)
        buff[i++] = ch;
    }
    //check for multi-line comment '/**/'
    else if(next=='*')
    {
        while((ch=fgetc(fp))!=EOF)
        {
            buff[i++] = ch;
            //check next char is / to know its multi line comment
            if(ch == '*')
            {
                char next2 = fgetc(fp);

                if(next2 == '/')
                {
                    buff[i++] = '/';
                    break;
                }
                else
                {
                    ungetc(next2, fp);
                }
            }
                
        }
    }
    else
    {
        return;
    }

    buff[i] = '\0';
    printf("COMMENTS : %s\n",buff);
}

//to handle identifier and keywords
void handle_identifier(FILE *fp,char ch)
{
    char buff[100];
    int i=0;

    buff[i++]=ch;

    while(isalnum(ch=fgetc(fp)) || ch=='_')
        buff[i++]=ch;

    buff[i]='\0';

    ungetc(ch,fp);

    if(is_keyword(buff))
        printf("KEYWORD : %s\n",buff);
    else
        printf("IDENTIFIER : %s\n",buff);
}

//to check for INTEGER or FLOAT CONSTANTS
void digits(FILE *fp,char ch)
{
    char buff[100];
    int i=0;
    int is_float=0;

    buff[i++]=ch;

    while(isdigit(ch=fgetc(fp)) || ch=='.')
    {
        if(ch=='.')
        {
            if(is_float)
                break;
            is_float=1;
        }

        buff[i++]=ch;
    }

    buff[i]='\0';

    ungetc(ch,fp);

    if(is_float)
        printf("FLOAT CONSTANT : %s\n",buff);
    else
        printf("INTEGER CONSTANT : %s\n",buff);
}

//chcek for OPERATORS
void handle_operator(FILE *fp,char ch)
{
    char next=fgetc(fp);

    if(ch=='=' && next=='=')
        printf("RELATIONAL OPERATOR : ==\n");

    else if(ch=='&' && next=='&')
        printf("LOGICAL OPERATOR : &&\n");

    else if(ch=='|' && next=='|')
        printf("LOGICAL OPERATOR : ||\n");

    else if(ch=='<'||ch=='>'||ch=='!')
    {
        if(next=='=')
            printf("RELATIONAL OPERATOR : %c=\n",ch);
        else
        {
            printf("OPERATOR : %c\n",ch);
            ungetc(next,fp);
        }
    }

    else
    {
        printf("OPERATOR : %c\n",ch);
        ungetc(next,fp);
    }
}