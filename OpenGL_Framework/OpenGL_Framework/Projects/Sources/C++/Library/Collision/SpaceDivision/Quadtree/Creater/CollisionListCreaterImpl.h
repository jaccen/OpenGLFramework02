//-------------------------------------------------------------
//!
//! @brief コリジョン
//! @brief 衝突関連の名前空間
//!
//-------------------------------------------------------------
namespace Collision
{
    //-------------------------------------------------------------
    //!
    //! @brief スペースディビジョン
    //! @brief 空間分割関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace SpaceDivision
    {
        //-------------------------------------------------------------
        //!
        //! @brief クアッドツリー
        //! @brief 4分木関連の名前空間
        //!
        //-------------------------------------------------------------
        namespace Quadtree
        {
            /*************************************************************//**
             *
             *  @brief  コンストラクタ
             *  @param  なし
             *
             ****************************************************************/
            template<typename T>
            C_CollisionListCreater<T>::C_CollisionListCreater()
            {
            }


            /*************************************************************//**
             *
             *  @brief  デストラクタ
             *  @param  なし
             *
             ****************************************************************/
            template<typename T>
            C_CollisionListCreater<T>::~C_CollisionListCreater()
            {
            }


            /*************************************************************//**
             *
             *  @brief  初期化処理を行う
             *  @param  領域の左端
             *  @param  領域の上端
             *  @param  領域の右端
             *  @param  領域の下端
             *  @param  空間のレベル( 0が基点 )
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::Initialize(float left,
                                                       float top,
                                                       float right,
                                                       float bottom,
                                                       uint32_t level)
            {
                // べき乗数値配列を求める
                CalculateExponentialValue(level);

                // 等比級数の和を使って空間数を求める
                cellNumber_ = (exponentialValues_[level + 1] - 1) / (4 - 1);

                // 線形空間を生成し、初期化
                upCells_ = std::make_unique<std::unique_ptr<C_Cell<T>>[]>(cellNumber_);

                // 空間のレベルを設定
                level_ = level;

                // 領域の設定
                SetTerritory(left, top, right, bottom);
            }


            /*************************************************************//**
             *
             *  @brief  ツリーのオブジェクトの登録を行う
             *  @param  境界範囲の左端
             *  @param  境界範囲の上端
             *  @param  境界範囲の右端
             *  @param  境界範囲の下端
             *  @param  ツリーのオブジェクト
             *  @return 正常終了：true
             *  @return 異常終了：false
             *
             ****************************************************************/
            template<typename T>
            bool C_CollisionListCreater<T>::Regist(float borderLeft,
                                                   float borderTop,
                                                   float borderRight,
                                                   float borderBottom,
                                                   S_TreeObject<T>* pTreeObject)
            {
                // 境界範囲から登録するモートン番号を取得
                uint32_t mortonNumber = GetMortonNumberFromAABB(borderLeft,
                                                                borderTop,
                                                                borderRight,
                                                                borderBottom);

                // 空間がない場合は、新しいセルを生成
                if (!upCells_[mortonNumber]) CreateCell(mortonNumber);

                // 空間にオブジェクトをプッシュ
                return upCells_[mortonNumber]->Push(pTreeObject);
            }


            /*************************************************************//**
             *
             *  @brief  衝突判定を行うオブジェクトのリストを取得する
             *  @param  衝突判定を行うオブジェクトのペアのリスト
             *  @param  衝突回数( 要素数の半分 )
             *  @return 正常終了：true
             *  @return 異常終了：false
             *
             ****************************************************************/
            template<typename T>
            bool C_CollisionListCreater<T>::GetCollisionList(std::deque<T*>* ppCollisionPairList,
                                                             uint32_t* pCollisionCount)
            {
                // ルート空間が作られているか確認
                if (!upCells_[0]) return false;

                // ルート空間の衝突判定リストを作成
                std::deque<T*> pCollisionStack;
                CreateCollisionList(0, &pCollisionStack, ppCollisionPairList);
                assert(pCollisionStack.size() == 0);

                // 衝突回数を取得
                (*pCollisionCount) = ppCollisionPairList->size() / 2;

                return true;
            }


            /*************************************************************//**
             *
             *  @brief  べき乗数値配列を計算する
             *  @param  空間のレベル( 0が基点 )
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::CalculateExponentialValue(uint32_t level)
            {
                // レベルに2追加( 配列のサイズを合わせるため )
                level += 2;

                // べき乗数値配列の領域を確保し、各レベルでの空間数を求める
                exponentialValues_.resize(level);

                exponentialValues_[0] = 1;

                for (size_t i = 1; i < level; ++i)
                {
                    exponentialValues_[i] = exponentialValues_[i - 1] * 4;
                }
            }


            /*************************************************************//**
             *
             *  @brief  領域の設定を行う
             *  @param  領域の左端
             *  @param  領域の上端
             *  @param  領域の右端
             *  @param  領域の下端
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::SetTerritory(float left,
                                                         float top,
                                                         float right,
                                                         float bottom)
            {
                // 左端と上端を設定
                left_ = left;
                top_ = top;

                // 領域の幅と高さを設定
                width_ = right - left;
                height_ = bottom - top;

                // 最小レベル空間の幅と高さを設定
                unitWidth_ = width_ / (1 << level_);
                unitHeight_ = height_ / (1 << level_);
            }


            /*************************************************************//**
             *
             *  @brief  境界範囲からモートン番号の取得を行う
             *  @param  境界範囲の左端
             *  @param  境界範囲の上端
             *  @param  境界範囲の右端
             *  @param  境界範囲の下端
             *  @return モートン番号
             *
             ****************************************************************/
            template<typename T>
            uint32_t C_CollisionListCreater<T>::GetMortonNumberFromAABB(float borderLeft,
                                                                        float borderTop,
                                                                        float borderRight,
                                                                        float borderBottom)
            {
                // 境界範囲の左上と右下の座標をモートン番号に変換
                uint32_t upperLeftMortonNumber = ConvertPointToMortonNumber(borderLeft, borderTop);
                uint32_t lowerRightMortonNumber = ConvertPointToMortonNumber(borderRight, borderBottom);

                // 左上と右下のモートン番号を排他的論理和
                uint32_t exclusiveOrMortonNumber = upperLeftMortonNumber ^ lowerRightMortonNumber;

                // 最上位レベル
                uint32_t highestLevel = 0;

                for (uint32_t i = 0, check2Bit = 0; i < level_; ++i)
                {
                    // 排他的論理和の結果を2進数での下位2bitを順に取得し、
                    // それが0以外ならば最上位レベルとして保持
                    check2Bit = (exclusiveOrMortonNumber >> (i * 2)) & 0x3;
                    if (check2Bit != 0) highestLevel = i + 1;
                }

                // 所属空間番号を左上のモートン番号を最上位レベルの2倍分シフトして求める
                uint32_t belongCellNumber = upperLeftMortonNumber >> (highestLevel * 2);

                // 等比級数の和から、所属空間番号に追加する値( 最初の要素の数 )を求め、追加
                uint32_t belongAddNumber = (exponentialValues_[level_ - static_cast<uint32_t>(highestLevel)] - 1) / (4 - 1);
                belongCellNumber += belongAddNumber;

                assert(belongCellNumber < cellNumber_);

                return belongCellNumber;
            }


            /*************************************************************//**
             *
             *  @brief  点をモートン番号へ変換する
             *  @param  X座標
             *  @param  Y座標
             *  @return モートン番号
             *
             ****************************************************************/
            template<typename T>
            uint32_t C_CollisionListCreater<T>::ConvertPointToMortonNumber(float positionX, float positionY)
            {
                assert(positionX - left_ >= 0);
                assert(positionY - top_ >= 0);

                // 最小レベル空間の幅と高さで割ったセル内の座標を整数値で求める
                uint32_t unitCellPositionX = static_cast<uint32_t>((positionX - left_) / unitWidth_);
                uint32_t unitCellPositionY = static_cast<uint32_t>((positionY - top_) / unitHeight_);

                return BitSeparate32(unitCellPositionX) | BitSeparate32(unitCellPositionY) << 1;
            }


            /*************************************************************//**
             *
             *  @brief  1bit飛びで32ビットに分割する
             *  @param  値
             *  @return 1bit飛びで32ビットに分割した値
             *
             ****************************************************************/
            template<typename T>
            uint32_t C_CollisionListCreater<T>::BitSeparate32(uint32_t value)
            {
                value = (value | (value << 8)) & 0x00ff00ff;
                value = (value | (value << 4)) & 0x0f0f0f0f;
                value = (value | (value << 2)) & 0x33333333;
                value = (value | (value << 1)) & 0x55555555;

                return value;
            }


            /*************************************************************//**
             *
             *  @brief  空間を作成する
             *  @param  配列の要素
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::CreateCell(uint32_t element)
            {
                while (!upCells_[element])
                {
                    // 指定の要素番号に空間を新規作成
                    upCells_[element] = std::make_unique<C_Cell<T>>();

                    // 親空間にジャンプ
                    element = (element - 1) >> 2;

                    // 要素がセルの数以上になった時点でループを抜ける
                    if (element >= cellNumber_) break;
                }
            }


            /*************************************************************//**
             *
             *  @brief  衝突判定を行うオブジェクトのリストを作成する
             *  @param  セルの要素
             *  @param  衝突判定を行うオブジェクトのスタック
             *  @param  衝突判定を行うオブジェクトのペアのリスト
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::CreateCollisionList(uint32_t cellElement,
                                                                std::deque<T*>* ppCollisionStack,
                                                                std::deque<T*>* ppCollisionPairList)
            {
                // 最後に登録したツリーのオブジェクトを取得
                S_TreeObject<T>* pTreeObject = upCells_[cellElement]->GetLastTreeObject();

                while (pTreeObject)
                {
                    // 最後に登録した次のツリーのオブジェクトを取得
                    S_TreeObject<T>* pAnotherTreeObject = pTreeObject->pNextObject_;

                    // 同空間内のオブジェクト同士の衝突判定リストを作成
                    while (pAnotherTreeObject)
                    {
                        (*ppCollisionPairList).push_back(pTreeObject->pObject_);
                        (*ppCollisionPairList).push_back(pAnotherTreeObject->pObject_);

                        // リンクしている次のオブジェクトへ切り替え
                        pAnotherTreeObject = pAnotherTreeObject->pNextObject_;
                    }

                    // 衝突判定を行うオブジェクトのスタックとの衝突判定リストを作成
                    for (auto& pCollisionObject : (*ppCollisionStack))
                    {
                        (*ppCollisionPairList).push_back(pTreeObject->pObject_);
                        (*ppCollisionPairList).push_back(pCollisionObject);
                    }

                    // リンクしている次のオブジェクトへ切り替え
                    pTreeObject = pTreeObject->pNextObject_;
                }

                // 子空間が存在するか判断するフラグ
                bool childCellFlag = false;

                // オブジェクトのカウンタ
                uint32_t objectCount = 0;

                for (size_t i = 0, nextElement = 0; i < 4; ++i)
                {
                    // 下位探索するための次の要素を計算
                    nextElement = cellElement * 4 + 1 + i;

                    if ((nextElement < cellNumber_) && (upCells_[nextElement]))
                    {
                        if (childCellFlag == false)
                        {
                            // 登録されているオブジェクトをスタックに追加
                            pTreeObject = upCells_[cellElement]->GetLastTreeObject();

                            while (pTreeObject)
                            {
                                ppCollisionStack->push_back(pTreeObject->pObject_);
                                pTreeObject = pTreeObject->pNextObject_;

                                // カウンタを1増加
                                ++objectCount;
                            }

                            // フラグを立てる
                            childCellFlag = true;
                        }

                        // 子空間で同じ処理を行う
                        CreateCollisionList(nextElement, ppCollisionStack, ppCollisionPairList);
                    }
                }

                // 子空間ができている場合、スタックからオブジェクトを外す
                if (childCellFlag == true) for (size_t i = 0; i < objectCount; ++i) ppCollisionStack->pop_back();
            }
        }
    }
}