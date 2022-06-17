# 최적화 알고리즘을 이용한 회귀식 추정
<br>

### 1. 회귀식
- 회귀식이란, 2개의 변수 X와 Y와의 사이에 Ŷ=f(X)+ε의 관계가 성립되고(ε는 평균적으로 0이라 기대되는 것), Y=f(X)는 변수 X의 변화에 대한 변수Y의 평균적인 변화방법을 주는 것이다. 

> 이와 같이 한쪽의 변수에서 다른쪽의 변수 값을 예측하기 위한 방정식을 회귀식이라 한다.(Y: 종속변수, X: 독립변수)

<br>

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

### 우선, 교재 속에 있는 예시로 유전 알고리즘을 구현해볼 것이다. 

> f(x) = $-x^2$ + 38x + 80  최댓값 찾는 유전자 알고리즘 구현.

유전 알고리즘에는 선택, 교차, 돌연변이 등 3개의 연산이 있다.

<br>

### 1. 선택(selection)연산

- **현재 세대의 후보해 중에서 우수한 후보해를 선택하는 연산**이다. 현재 세대에 n개의 후보해가 있으면, 적합도가 상대적으로 낮은 후보해들은 선택되지 않을 수도 있는 것이다.

- 룰렉 휠(roulette wheel) 방법으로 선택 연산을 구현할 수 있다.
- 
![image](https://user-images.githubusercontent.com/102197100/174352342-ed297637-b278-4a45-a4b1-4c3cbc7809ee.png)


<br>

### 2. 교차(crossover)연산


<br>

### 3. 돌이변이(mutation)연산
![image](https://user-images.githubusercontent.com/102197100/174352408-34f1054f-fd96-45dd-ac1e-103641179c6d.png)
