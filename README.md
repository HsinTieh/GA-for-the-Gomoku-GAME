# 超啟發式之基因演算法解五子棋問題
## Super Heuristic Genetic Algorithm for Gomoku Problem

> ### 五子棋簡介
  >> * 五子棋是一個在二維棋盤上雙方輪流落子的遊戲，在任一方向(橫向、縱向、左斜、右斜)連成五子者獲勝。<br>
  >> * 本研究所設計的五子棋並無任何規則限制。<br>
  >> * 本研究利用**基因演算法**，建立一個能與人對戰的五子棋程式和機器與機器對戰。<br>

> ### 參數設定
  >> 棋盤結構 : 15*15 <br>
  >> 編碼方式 : 去邊界後從未下棋的位置隨機選取<br>
  >> 染色體長度 : 7<br>
  >> 生存率 :  0.1<br>
  >> 突變率 : 0.01<br>
  >> 最大群體限制 : 1000<br>
  >> 時間限制 :  5s/10s<br>

> ### 基本架構
 >>![GITHUB](./image/gomoku_architecture1.PNG)
 >>1. 建立初始的群體<br>
 >>2. 計算適應函數(權重)<br>
 >>3. 選擇基因 (Selection)<br>
 >>4. 交配 (Crossover)<br>
 >>5. 突變 (Mutation)<br>
 >>6. 排序所有適應度的群體<br>
 >>7. 計算目前最優的位置<br>
 >>8. 輸出最優的位置<br>
