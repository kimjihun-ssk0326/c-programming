#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 

struct Movie {
    char title[100];
    char director[50];
    int release_year;
    float rating;
};

void inputMovie(struct Movie* m)
{
    printf("제목:");
    gets(m->title);
    printf("감독:");
    scanf("%s",m->director)
    
}
void printMovie(const struct Movie* m);

int main(void)
{
    struct Movie s = {};
    struct Movie* m;ㄴㄴㄴ
    m = &s;
    for (int i = 0;i < 3;i++)
    {
        printf("영화 %d 정보\n",i);
        printf("제목: %s\n",s.title);
        printf("감독: %s\n", s.director);
        printf("개봉 연도: %d\n", s.release_year);
        printf("평점: %d\n", s.rating);
    }
 
}
 
int main(void)
{
    struct Movie movies[NUM_MOVIES];
    for (int i = 0;i < NUM_MOVIES;i++)
    {

    }
}