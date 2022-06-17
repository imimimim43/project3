#include <stdio.h>
#include <time.h>
#include <math.h>

double final_fitness[100]; // n이 최대 100이라 가정.

int fitness_funct(int x) { // 식에 대입해주는 함수
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

int decimal(int arr[5]) { //2진수를 10진수으로 변환
    int sum = 0;
    int n = sizeof(arr);
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) sum += pow(2, i);
    }
    return sum;
}
void binary(int x, int y, int cross1[], int cross2[]) { // 10진수를 2진수로 바꾸기
    int value_binary1[5] = { 0 }; 
    int value_binary2[5] = { 0 };
    
    int p = 0;
    while (x)
    {
        value_binary1[p++] = x % 2;
        x /= 2;
    }
    
    int q = 0;
    while (y)
    {
        value_binary2[q++] = y % 2;
        y /= 2;
    }

    //교차 연산
    for (int i = 0; i < 5; i++) {
        if (i >= 0 && i < 2) {
            cross1[i] = value_binary1[i];
            cross2[i] = value_binary2[i];
        }
        else if (i >= 2) {
            cross1[i] = value_binary2[i];
            cross2[i] = value_binary1[i];
        }
    }
}

void mutate(int arr[]) {  //돌연변이 연산
    if (arr[3] == 0)arr[3] = 1; // 2번째 값을 변경시키기, 배열을 반대로 넣었으므로 3번 인덱스의 값을 변경하기
    else if (arr[3] == 1)arr[3] = 0;
    for (int i = 4; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
}

int main(void) {
    int n;
    srand(time(NULL));
    printf("회전 횟수 : ");
    scanf_s("%d", &n); // 코드 실행을 n번 실행시키기
    int temp = n;
    int cnt = 1;
    int candidates[4];
    int final_candidates[4];
    while (n > 0) {

        if (cnt == 1) { // 처음 후보생들만 랜덤으로 바꾸기
            for (int i = 0; i < 4; i++) {
                candidates[i] = rand() % 32 + 1;
            }
        }
        else if(cnt != 1){
            for (int i = 0; i < 4; i++) {
                candidates[i] = final_candidates[i];
            }

        }

        printf("%d번째 후보들: ", cnt);
        for (int i = 0; i < 4; i++) {
            printf("%d ", candidates[i]);
        }
        int fitness[4];
        double roulette[4];
        int roulette_value[4];
        int cross1[5];
        int cross2[5];
        int cross3[5];
        int cross4[5];

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
        binary(roulette_value[0], roulette_value[2], cross1, cross2);
        printf("\n");
        printf("%d %d\n", roulette_value[1], roulette_value[3]);
        binary(roulette_value[1], roulette_value[3], cross3, cross4);
        printf("\n");
        mutate(cross1);//후보해 1만 바꿔주기
        printf("\n");
        printf("^^ :%d", decimal(cross1));
        final_candidates[0] = decimal(cross1);
        final_candidates[1] = decimal(cross2);
        final_candidates[2] = decimal(cross3);
        final_candidates[3] = decimal(cross4);
        for (int i = 0; i < 4; i++) {
            printf("%0.2lf ", final_candidates[i]);
        }
        printf("\n");
        cnt++;
        n--;
    }
    printf("적합도: \n");
    for (int i = 0; i < temp; i++) {
        printf("%d : %0.2lf ", i, final_fitness[i]);
    }
    return 0;
}
