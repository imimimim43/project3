#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

double final_fitness[100]; // n이 최대 100이라 가정.

int fitness_funct(int x) {
   int result;
   result = -x * x + 38 * x + 80;
   return result;
}

int selection(double arr[], int arr2[]) {
   int a = rand() % 100 + 1;
   printf("랜덤 비율: %d%%\n", a);
   if ((0 < a) && (a <= arr[0])) {
      return arr2[0];
   }
   else if ((arr[0] < a) && (a <= arr[0] + arr[1])) {
      return arr2[1];
   }
   else if ((arr[0] + arr[1] < a) && (a <= arr[0] + arr[1] + arr[2])) {
      return arr2[2];
   }
   else if ((arr[0] + arr[1] + arr[2] < a) && (a <= arr[0] + arr[1] + arr[2] + arr[3])) {
      return arr2[3];
   }
}

double Total_fitness(int fitness[], int candidates[], int a) {
   double sum = 0;
   for (int i = 0; i < 4; i++) {
      fitness[i] = fitness_funct(candidates[i]);
      sum += fitness_funct(candidates[i]);
   }
   printf("\n");
   printf("y(x) 대입하면 : ");
   for (int i = 0; i < 4; i++) {
      printf("%d ", fitness[i]);
   }
   double arg = sum / 4;
   final_fitness[a - 1] = arg;
   printf("\n");
   printf("적합도 합, 적합도 평균: %0.lf, %0.2lf", sum, arg);
   return arg;
}

int decimal(int arr[5]) { //2진수 -> 10진수 변환
   int sum = 0;
   int n = sizeof(arr);
   for (int i = 0; i < n; i++) {
      if (arr[i] == 1) sum += pow(2, i);
   }
   printf("%d", sum);
   return sum;
}
void binary(int x, int y, int cross_x[], int cross_y[]) {
   int p = 0; int q = 0;
   int binary_x[5] = { 0 }; int binary_y[5] = { 0 };
   //x를 2진수로 바꾸기
   while (x)
   {
      binary_x[p++] = x % 2;
      x /= 2;
   }
   printf("x: ");
   for (int i = 4; i >= 0; i--) {
      printf("%d ", binary_x[i]);
   }
   //y를 2진수로 바꾸기
   while (y)
   {
      binary_y[q++] = y % 2;
      y /= 2;
   }
   printf("\n");
   printf("y: ");
   for (int i = 4; i >= 0; i--) {
      printf("%d ", binary_y[i]);
   }

   //교차 연산
   for (int i = 0; i < 5; i++) {
      if (i >= 0 && i < 2) {
         cross_x[i] = binary_x[i];
         cross_y[i] = binary_y[i];
      }
      else if (i >= 2) {
         cross_x[i] = binary_y[i];
         cross_y[i] = binary_x[i];
      }
   }

   printf("\ncross_x: ");
   for (int i = 4; i >= 0; i--) { // 4 3 2 1 0,  01000
      printf("%d ", cross_x[i]);
   }
   printf("\ncross_y: ");
   for (int i = 4; i >= 0; i--) {
      printf("%d ", cross_y[i]);
   }
}

void mutate(int arr[]) {  //돌연변이 연산
   if (arr[3] == 0)arr[3] = 1;
   else if (arr[3] == 1)arr[3] = 0;
   printf("mutate(3번) : ");
   for (int i = 4; i >= 0; i--) {
      printf("%d ", arr[i]);
   }
}

int main(void) {
   int n;
   srand(time(NULL));
   printf("회전 횟수 : ");
   scanf_s("%d", &n);
   int temp = n;
   int cnt = 1;

   while (n > 0) {
      int cross_x[5];
      int cross_y[5];
      int candidates[4];
      int fitness[4];
      double roulette[4];
      int roulette_value[4];

      for (int i = 0; i < 4; i++) {
         candidates[i] = rand() % 32 + 1;
      }

      printf("%d번째 후보들: ", cnt);
      for (int i = 0; i < 4; i++) {
         printf("%d ", candidates[i]);
      }

      Total_fitness(fitness, candidates, cnt);

      printf("\n");
      double sum = 0;
      for (int i = 0; i < 4; i++) {
         sum += fitness_funct(candidates[i]);
      }
      for (int i = 0; i < 4; i++) {
         roulette[i] = round(fitness[i] / sum * 100);
      }
      printf("룰렛의 값: ");
      for (int i = 0; i < 4; i++) {
         printf("%0.lf ", roulette[i]);
      }
      printf("\n");
      for (int i = 0; i < 4; i++) {
         roulette_value[i] = selection(roulette, candidates);
         printf("룰렛 값: %d\n", roulette_value[i]);
      }

      printf("\n");
      printf("%d %d\n", roulette_value[0], roulette_value[2]);
      binary(roulette_value[0], roulette_value[2], cross_x, cross_y);
      printf("\n");
      printf("%d %d\n", roulette_value[1], roulette_value[3]);
      binary(roulette_value[1], roulette_value[3], cross_x, cross_y);
      printf("\n");
      mutate(cross_x);
      printf("\n");
      cnt++;
      n--;
   }
   printf("총 적합도: \n");
   for (int i = 0; i < temp; i++) {
      printf("%0.2lf ", final_fitness[i]);
   }
   return 0;
}
