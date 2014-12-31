/* ヘッダファイル */
#include "../StaticLibrary/StaticLibrary.h"
#include "../../Game/ConnectWars/ConnectWars.h"


/* リリース時 */
#ifndef _DEBUG


// サブシステムをWindowsに変更し、エントリーポイントをmain関数とする
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


#endif


/*************************************************************//**
 *
 *  @brief  メイン関数
 *  @param  コマンドラインから渡された引数の数
 *  @param  コマンドラインの引数として渡された文字列
 *  @return 正常終了：0
 *  @return 異常終了：-1
 *
 ****************************************************************/
int main(int argc, char* argv[])
{
    // ゲームを生成し、実行
    auto pGame = std::make_unique<ConnectWars::C_ConnectWars>();
    if (pGame->Run() == false) return -1;

    return 0;
}
