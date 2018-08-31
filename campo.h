#ifndef CAMPO_H
#define CAMPO_H


class campo
{
    public:
        campo(char name[20],int t);
        char nombre[20];
        int tipo;
        int longitud;
        campo * sig;
        char * toChar();
        void initFromChar(char * data);
        //Crear tochar y init en campoDatos y en registro
};

#endif // CAMPO_H
