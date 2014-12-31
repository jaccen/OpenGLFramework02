:: [ バッチファイル説明 ]
:: 実行するとプロジェクト内の不要なフォルダとファイルが削除されます。
:: 削除されるフォルダはその階層内のDebug, Release, ipchフォルダです。
:: また、….ncb, ….suo, ….user, ….sdf が拡張子のファイルも同時に削除されます。


:: 実行時のコマンドを非表示
@echo off


echo プロジェクトの不要なファイルとフォルダを削除します。

:: 不要なファイルとフォルダを削除
call :delfiles

echo 削除が完了しました。

:: キー入力を待機
pause


exit /b


:sub


cd %1
call :delfiles
cd ..


exit /b


:: 不要なフォルダとファイルを削除するサブルーチン
:delfiles


if exist Debug rmdir /s /q Debug
if exist Release rmdir /s /q Release
if exist ipch rmdir /s /q ipch
if exist *.ncb del *.ncb
if exist *.suo del /A:H *.suo
if exist *.user del *.user
if exist *.sdf del *.sdf
if exist *.opensdf del /A:H *.opensdf


exit /b


:: [ メモ ]
:: if exist ファイル名 でそのファイルが存在する際true
:: rmdir はそのフォルダを削除。
:: この後に/sをつけることでそのフォルダ内もファイルもすべて削除。
:: /qをつけることで削除時の確認をなしにする。
:: /A:Hは隠しファイルであることを示す。