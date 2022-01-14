# 110-PD Final Project / Group-11: GTD 系統
## 開發環境與編輯器
    - winodows 10
    - vscode
    - g++ compiler
## 注意事項
### compile
- 請用 **Big 5** 編碼讀寫所有檔案
- 如果是有 project 的開發環境可以直接 compile & run
- 如果是 vscode 必須將 task.json 的 args 部分改成
```
"args": [
			"-fdiagnostics-color=always",
			"-g",
			"${workspaceFolder}\\*.cpp",
			"-o",
			"main.exe"
		]
```
### run
- 在您的路徑下開啟 main.exe
- 輸入時可以輸入中文
- 輸入時請盡可能輸入合理數值
- 若需將所有目標等資料刪除重新執行，則在 data/data.txt 僅留下 "0" 即可
- 若需將所有獎賞刪除重新執行，則在 data/reward.txt 留下 "0 0" 即可
### bugs
- 排版可能因為電腦螢幕、系統...等因素跑掉，敬請見諒
- 流程上若有邏輯上的瑕疵，敬請見諒
- 若輸入空白鍵會導致程式出現錯誤，如需輸入請用 '_' 或 '-' 代替
- 並沒有將所有例外情況清理乾淨，如輸入型別錯誤、輸入日期不合理

