# 최적화 알고리즘을 이용한 회귀식 추정
<br>

### 1. 회귀식
- 회귀식이란, 2개의 변수 X와 Y와의 사이에 Ŷ=f(X)+ε의 관계가 성립되고(ε는 평균적으로 0이라 기대되는 것), Y=f(X)는 변수 X의 변화에 대한 변수Y의 평균적인 변화방법을 주는 것이다. 

> 이와 같이 한쪽의 변수에서 다른쪽의 변수 값을 예측하기 위한 방정식을 회귀식이라 한다.(Y: 종속변수, X: 독립변수)

<br>

![image](https://user-images.githubusercontent.com/102197100/174389133-40510aa9-dcac-4c99-8200-aa8999280762.png)

<br>

- 회귀식 추정으로는 기후변화 시나리오에 따른 우리나라 주변해역의 해수면 상승 전망 그래프를 하려고 한다. 그 중에서도 지구 온난화가 제일 완화되었을 때의 그래프인 RCP 2.6 파란색 그래프를 추정할 것이다. 위 그래프를 x와 y 관계로 아래와 같이 표에 나타내보면, 

<br>

![image](https://user-images.githubusercontent.com/102197100/174390888-aba3468d-e74c-44f3-91a5-ed21a7274cf2.png)


x의 값이 커질수록 y의 값이 커지는 정비례의 1차 그래프이며, 오른쪽으로 갈수록 그래프의 기울기가 작아지는 것을 알 수 있다. 맨 처음 값의 y가 0이므로 b의 값은 0이며 그래프에서 찾아할 값은 a이라고 정할 수 있다. 표를 살펴본 결과 식은 약 y = f(x) = 1/2x+b가 나올거라 예상이 되고 a의 값은 유전 알고리즘을 구현하여 찾을 것이다. 


## 유전 알고리즘(Genetic Algorithm)
- 다윈의 진화론으로부터 창안된 해 탐색 알고리즘이며, 최적화 문제를 해결하는데 '적자생존'의 개념을 적용한 것이다.

---

### 유전 알고리즘 간단하게 요약.


<ol>
<li> n개의 후보해로 염색체 표현. [첫 세대 구성]</li>
<li> 각 염색체들의 적합도 계산.</li>
<li> 만족스러운 후보해가 존재하는지 확인.</li>
<li> 다음 세대의 n개 염색체 생성.</li>
</ol>

---
![image](https://user-images.githubusercontent.com/102197100/174352197-7330977e-bf69-48c1-8ec4-7a398800f8c5.png)
<br>

### 우선, 교재 속에 있는 예시로 유전 알고리즘을 구현해볼 것이다. 이번 개념은 전보다 훨씬 어려워, 자바가 아닌 c언어로 구현할 것이다.

> f(x) = $-x^2$ + 38x + 80  최댓값 찾는 유전자 알고리즘 구현.

유전 알고리즘에는 선택, 교차, 돌연변이 등 3개의 연산이 있다.

<br>

### 1. 선택(selection)연산

- **현재 세대의 후보해 중에서 우수한 후보해를 선택하는 연산**이다. 현재 세대에 n개의 후보해가 있으면, 적합도가 상대적으로 낮은 후보해들은 선택되지 않을 수도 있는 것이다.

- 룰렉 휠(roulette wheel) 방법으로 선택 연산을 구현할 수 있다.

> 각 후보해의 적합도를 전체 적합도로 나누면 룰렛의 비율을 구할 수 있다.

<br>

![image](https://user-images.githubusercontent.com/102197100/174352342-ed297637-b278-4a45-a4b1-4c3cbc7809ee.png)

-> 랜덤의 후보해를 교재와 같이 1, 29, 3, 10으로 가정하고 f(x)에 대입하여 적합도를 구해준다. 그 다음, sum_fitness(적합도의 총합)으로 나눠주면 각 후보해의 룰렛 면적을 구할 수 있다. 랜덤의 값을 n개만큼 뽑아 해당하는 원반의 면적의 후보해 값을 선택해주면 된다. 

<br>

### 2. 교차(crossover)연산

- 선택 연산을 수행한 후의 **후보해 사이에 수행되는데, 이는 염색체가 교차하는 것을 그대로 모방한 것**이다.(두 값을 교차로 바꾼다고 생각하면 됨.) 아래 그림은 교차 연산의 예시인데, 후보해 2인 29와 후보해 4인 10을 2진수로 바꾸고 1점-교차 연산을 위해 그림의 교차점에서 바꿔준다.

<br>

![image](https://user-images.githubusercontent.com/102197100/174352408-34f1054f-fd96-45dd-ac1e-103641179c6d.png)

<br>

### 3. 돌이변이(mutation)연산

- **아주 작은 확률로 후보해의 일부분을 임의로 변형시키는 것**이다. 이 확률을 돌연변이율(mutation rate)이라고 하며, 일반적으로 (1/PopSize)~(1/Length)의 범위에서 사용된다. 교재에서는 두번째 bit가 바뀌어 코드에도 두번째 bit가 바뀌도록 적용시켰다. 

## 코드 구현

■ 필요한 요소
<br>
- n번째 실행되는 최적값을 저장하기 위한 배열
- 후보들을 저장하기 위한 배열
- 적합도를 저장하기 위한 배열
- 룰렛의 값을 저장하기 위한 배열

 **코드에 쓰일 배열 선언**
 
```

int fitness[4]; // 적합도를 저장하기 위한 배열
double roulette[4]; int roulette_value[4]; // 룰렛의 값과, 룰렛 면적의 값을 나타내는 배열
int cross1[5]; // 교차된 값을 나타내기 위한 배열
final_fitness[100]; // 최종 적합도를 저장하기 위한 배열

```

<br>

**선택 연산 코드 구현**

```

int selection(double arr[], int arr2[]) {
    int ratio = rand() % 100 + 1;
    if ((0 < ratio) && (ratio <= arr[0])) {
        return arr2[0];
    }
    else if ((arr[0] < ratio) && (ratio <= arr[0] + arr[1])) {
        return arr2[1];
    }
    else if ((arr[0] + arr[1] < ratio) && (ratio <= arr[0] + arr[1] + arr[2])) {
        return arr2[2];
    }
    else if ((arr[0] + arr[1] + arr[2] < ratio) && (ratio <= arr[0] + arr[1] + arr[2] + arr[3])) {
        return arr2[3];
    }
}

```

<br>



**교차 연산 코드 구현**

```

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
```


**돌연변이 연산 코드 구현**

```
void mutate(int arr[]) {  //돌연변이 연산
    if (arr[3] == 0)arr[3] = 1; // 2번째 값을 변경시키기, 배열을 반대로 넣었으므로 3번 인덱스의 값을 변경하기
    else if (arr[3] == 1)arr[3] = 0;
    for (int i = 4; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
}

```


**메인 코드 구현**

```
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
```
 
 
## **최종 코드 구현**

```

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
	
```

**오류 발생**

- candidates 배열의 값이 이동되지 않는 일 발생, 배열이 아닌 다른 방법을 탐색하는 것이 좋을 것 같음. n의 최적값을 구하는 코드는 구현하기 성공.
