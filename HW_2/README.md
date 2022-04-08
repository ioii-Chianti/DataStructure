### 13460 - Happy Farm
[Link Here.](https://acm.cs.nthu.edu.tw/problem/13460/)

#### Insert (nonempty)
+ cur < newNode -> keep traverse
+ cur == newNode -> check fence
+ newNode < cur -> insert between pre and cur

#### Delete (nonempty)
+ cur == targetNode -> check fence and delete
+ cur != targetNode -> keep traverse