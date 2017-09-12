#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFSIZE 2048

typedef struct{
    int fd;
    char * buf;
    int offset;
} mFILE;

char tabText[] = "Du bon Texte";
char tab2Text[] = "Du meilleur Texte";
char tab3Text[] = "le meilleur des textes";



mFILE * mfopen(const char * streamToOpen){
    mFILE * res = malloc(sizeof(mFILE));
    
    res->buf = malloc(sizeof(char) * BUFSIZE);
    res->fd = open(streamToOpen, O_RDWR);
    if(res->fd == -1){
        perror("Error: ");
        exit(-1);
    }
    res->offset = 0;

    
    return res;
}

int mfflush(mFILE * f){
    write(f->fd, f->buf, f->offset);
    f->offset = 0;
    return 0;
}

int mfclose(mFILE * f){
    if(f->offset !=0){
        mfflush(f);
    }
    free(f->buf);
    free(f);
    close(f->fd);
    return 0;
}

int mfputc(mFILE * f, char c){
    int taille = f->offset++;
    if(taille >= 1024)
        write(f->fd, f->buf, f->offset);
    else
        f->buf[f->offset++] = c;
    return 0;
}

char mfgetc(mFILE * f){
    if(f->offset == BUFSIZE){
        read(f->fd, f->buf, BUFSIZE);
        f->offset = 0;
    }
    return f->buf[f->offset++];
}

int mfstat(mFILE * f){

    struct stat *  s = malloc(sizeof(struct stat));
    fstat(f->fd, s);
    printf("%lu \n", s->st_ino);
    return 0;
}

int main(void){
    mFILE * f = mfopen("Exo2.txt");
    mfstat(f);
    return 0;
}