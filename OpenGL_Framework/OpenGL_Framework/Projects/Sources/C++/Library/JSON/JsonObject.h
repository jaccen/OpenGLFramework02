/* 二重インクルード防止 */
#pragma once


/* マクロ定義 */
#define JSON_ENABLE_INSERT_TAB 


/* ヘッダファイル */
#include "JsonDefine.h"


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON関連のクラスや関数などに付ける名前空間
///
//-------------------------------------------------------------
namespace JSON
{
    //-------------------------------------------------------------
    //!
    //! @brief JSONオブジェクト
    //! @brief JSONのデータを扱うためのクラス
    //!
    //-------------------------------------------------------------
    template <template<typename T>class Allocator = std::allocator, 
              typename AllocateObject = S_DefaultAlloc,
              typename FreeObject = S_DefaultFree>
    class C_JsonObject
    {
    public:

#pragma region 別名
    
        using JsonObject = C_JsonObject<Allocator, AllocateObject, FreeObject>;             // JsonObject型
        using Character = char;                                                             // Character型
        using Integer = int32_t;                                                            // Integer型
        using Real = double;                                                                // Real型
        using Boolean = bool;                                                               // Boolean型
        using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;    // String型
        using Array = std::vector<JsonObject, Allocator<JsonObject>>;                       // Array型
        using Object = std::unordered_map<String,                                           // Object型
                                          JsonObject,
                                          std::hash<String>,
                                          std::equal_to<String>,
                                          Allocator<std::pair<String, JsonObject>>>;

#pragma endregion

    private:

#pragma region タイプサイズ構造体

        //-------------------------------------------------------------
        //!
        //! @brief タイプサイズ
        //! @brief 各種類のサイズを表す構造体
        //!
        //-------------------------------------------------------------
        template<ecDataType dataType>
        struct S_TypeSize
        {
            static const std::size_t s_size = 0;                                            ///< @brief 型のサイズ
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_INTEGER>
        {
            static const std::size_t s_size = sizeof(Integer);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_REAL>
        {
            static const std::size_t s_size = sizeof(Real);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_BOOLEAN>
        {
            static const std::size_t s_size = sizeof(Boolean);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_STRING>
        {
            static const std::size_t s_size = sizeof(String);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_ARRAY>
        {
            static const std::size_t s_size = sizeof(Array);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_OBJECT>
        {
            static const std::size_t s_size = sizeof(Object);
        };

#pragma endregion

#pragma region コンテナ操作クラス

        //-------------------------------------------------------------
        //!
        //! @brief アラライオペレーション
        //! @brief 配列操作を行うためのクラス
        //!
        //-------------------------------------------------------------
        class C_ArrayOperation
        {
        public:
            /*************************************************************//**
             *
             *  @brief  コンストラクタ
             *  @param  Jsonオブジェクト
             *
             ****************************************************************/
            C_ArrayOperation(JsonObject* pJsonObject) :

                // Jsonオブジェクト
                pJsonObject_(pJsonObject)

            {
            }


            /*************************************************************//**
             *
             *  @brief  デストラクタ
             *  @param  なし
             *
             ****************************************************************/
            ~C_ArrayOperation()
            {
            }


            /*************************************************************//**
             *
             *  @brief  要素の追加を行う
             *  @param  なし
             *  @return なし
             *
             ****************************************************************/
            void Add()
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                rArray.emplace_back();
            }

            /*************************************************************//**
             *
             *  @brief  要素の削除を行う
             *  @param  なし
             *  @return なし
             *
             ****************************************************************/
            void Erase(Integer index)
            {
                auto& rArray = *pJsonObject_->ArrayCast();

                if (rArray.size() > index)
                {
                    auto iterator = rArray.begin() + index;
                    rArray.erase(iterator);
                }
            }


            /*************************************************************//**
             *
             *  @brief  メモリの確保を行う
             *  @param  メモリサイズ
             *  @return なし
             *
             ****************************************************************/
            void Reserve(Integer size)
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                rArray.reserve(size);
            }


            /*************************************************************//**
             *
             *  @brief  要素数を取得する
             *  @param  なし
             *  @return なし
             *
             ****************************************************************/
            std::size_t GetSize() const
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                return rArray.size();
            }


            /*************************************************************//**
             *
             *  @brief  要素数を取得する
             *  @param  なし
             *  @return なし
             *
             ****************************************************************/
            std::size_t GetCapacity() const
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                return rArray.capacity();
            }


            /*************************************************************//**
             *
             *  @brief  添え字演算子のオーバーロード
             *  @param  インデックス
             *  @return なし
             *
             ****************************************************************/
            JsonObject& operator[](std::size_t index)
            {
                auto pJsonObject = GetJsonObject(index);

                while (pJsonObject == nullptr)
                {
                    std::size_t capacity = GetCapacity();
                    if (capacity < index) Reserve(capacity + 16);
                    
                    Add();
                    pJsonObject = GetJsonObject(index);
                }

                return *pJsonObject;
            }
        private:
            JsonObject* pJsonObject_ = nullptr;                                             ///< @brief Jsonオブジェクト

            /*************************************************************//**
             *
             *  @brief  Jsonオブジェクトを取得する
             *  @param  なし
             *  @return なし
             *
             ****************************************************************/
            JsonObject* GetJsonObject(std::size_t index)
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                if (index < rArray.size()) return &rArray[index];
                
                return nullptr;
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief オブジェクトオペレーション
        //! @brief 連想配列操作を行うためのクラス
        //!
        //-------------------------------------------------------------
        class C_ObjectOperation
        {
        public:
            /*************************************************************//**
             *
             *  @brief  コンストラクタ
             *  @param  JSONオブジェクト
             *
             ****************************************************************/
            C_ObjectOperation(JsonObject* pJsonObject) : 

                // Jsonオブジェクト
                pJsonObject_(pJsonObject)

            {
            }


            /*************************************************************//**
             *
             *  @brief  デストラクタ
             *  @param  なし
             *
             ****************************************************************/
            ~C_ObjectOperation()
            {
            }


            /*************************************************************//**
             *
             *  @brief  先頭を指すイテレータを取得する
             *  @param  なし
             *  @return 先頭を指すイテレータ
             *
             ****************************************************************/
            typename Object::iterator Begin()
            {
                return pJsonObject_->ObjectCast()->begin();
            }


            /*************************************************************//**
             *
             *  @brief  末尾を指すイテレータを取得する
             *  @param  なし
             *  @return 末尾を指すイテレータ
             *
             ****************************************************************/
            typename Object::iterator End()
            {
                return pJsonObject_->ObjectCast()->end();
            }


            /*************************************************************//**
             *
             *  @brief  キーからJSONオブジェクトを検索する
             *  @param  キー
             *  @return JSONオブジェクト
             *
             ****************************************************************/
            JsonObject* Find(const String& rKey)
            {
                auto& rObject = *pJsonObject_->ObjectCast();

                auto iterator = rObject.find(rKey);
                if (iterator != rObject.end()) return &(iterator->second);

                return nullptr;
            }


            /*************************************************************//**
             *
             *  @brief  JSONオブジェクトを挿入する
             *  @param  キー
             *  @return Jsonオブジェクト
             *
             ****************************************************************/
            JsonObject* Insert(const String& rKey)
            {
                auto& rObject = *pJsonObject_->ObjectCast();
                auto iterator = rObject.emplace(rKey, JsonObject(rKey)).first;

                return &(iterator->second);
            }


            /*************************************************************//**
             *
             *  @brief  JSONオブジェクトを除去する
             *  @param  キー
             *  @return なし
             *
             ****************************************************************/
            void Erase(const String& rKey)
            {
                auto rObject = pJsonObject_->ObjectCast();

                auto iterator = rObject.find(rKey);
                if (iterator != rObject.end()) rObject.erase(iterator);
            }
        private:
            JsonObject* pJsonObject_ = nullptr;                                             ///< @brief Jsonオブジェクト
        };

#pragma endregion

    public:

#pragma region publicメンバ関数

        /*************************************************************//**
         *
         *  @brief  デフォルトコンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_JsonObject() = default;


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  キー
         *
         ****************************************************************/
        C_JsonObject(const String& rKey) :
            
            // キー
            key_(rKey)

        {
        }


        /*************************************************************//**
         *
         *  @brief  コピーコンストラクタ
         *  @param  JSONオブジェクト
         *
         ****************************************************************/
        C_JsonObject(const JsonObject& rOther) = delete;


        /*************************************************************//**
         *
         *  @brief  ムーブコンストラクタ
         *  @param  JSONオブジェクト
         *
         ****************************************************************/
		C_JsonObject(JsonObject&& rrOther)
        {
            *this = std::move(rrOther);
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param なし
         *
         ****************************************************************/
        ~C_JsonObject()
        {
            DataFree();
        }


        /*************************************************************//**
         *
         *  @brief  配列操作のオブジェクトを取得する
         *  @param  なし
         *  @return 配列操作のオブジェクト
         *
         ****************************************************************/
        C_ArrayOperation GetArrayOperation()
        {
            return C_ArrayOperation(this);
        }


        /*************************************************************//**
         *
         *  @brief  連想配列操作のオブジェクトを取得する
         *  @param  なし
         *  @return 連想配列操作のオブジェクト
         *
         ****************************************************************/
        C_ObjectOperation GetObjectOperation()
        {
            return C_ObjectOperation(this);
        }


        /*************************************************************//**
         *
         *  @brief  キーを取得
         *  @param  なし
         *  @return キー
         *
         ****************************************************************/
        const String& GetKey() const
        {
            return key_;
        }


        /*************************************************************//**
         *
         *  @brief  値を取得
         *  @param  なし
         *  @return 値
         *
         ****************************************************************/
        template<typename T>
        T GetValue() const
        {
        }


        /*************************************************************//**
         *
         *  @brief  値を取得
         *  @param  なし
         *  @return 整数
         *
         ****************************************************************/
        template<>
        Integer GetValue<Integer>() const
        {
            return *IntegerCast();
        }


        /*************************************************************//**
         *
         *  @brief  値を取得
         *  @param  なし
         *  @return 実数
         *
         ****************************************************************/
        template<>
        Real GetValue<Real>() const
        {
            return *RealCast();
        }


        /*************************************************************//**
         *
         *  @brief  値を取得
         *  @param  なし
         *  @return bool値
         *
         ****************************************************************/
        template<>
        Boolean GetValue<Boolean>() const
        {
            return *BooleanCast();
        }


        /*************************************************************//**
         *
         *  @brief  値を取得
         *  @param  なし
         *  @return 文字列
         *
         ****************************************************************/
        template<>
        String GetValue<String>() const
        {
            return *StringCast();
        }


        /*************************************************************//**
         *
         *  @brief  値を取得
         *  @param  なし
         *  @return 文字列
         *
         ****************************************************************/
        const char* GetTypeName() const
        {
            return GetTypeName(dataType_);
        }


        /*************************************************************//**
         *
         *  @brief  配列として作り直す
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void RemakeAsArray()
        {
            if (DataAlloc<ecDataType::TYPE_ARRAY>() == true) Construct<Array>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  連想配列として作り直す
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void RemakeAsObject()
        {
            if (DataAlloc<ecDataType::TYPE_OBJECT>() == true) Construct<Object>(pValue_);
        }

#pragma endregion

#pragma region public静的メンバ関数

        /*************************************************************//**
         *
         *  @brief  文字列からJSONオブジェクトを作成する
         *  @param  文字列
         *  @return JSONオブジェクト
         *
         ****************************************************************/
        static JsonObject s_CreateFromString(const String& rString)
        {
            // 文字列の長さとメモリのサイズ
            int32_t stringLength = rString.length();
            int32_t memorySize = stringLength + 1;

            // メモリ割り当てオブジェクト
            AllocateObject allocateObject;

            // 文字列をコピー
            std::unique_ptr<char, FreeObject> upCopyString(reinterpret_cast<char*>(allocateObject(memorySize)));
            std::memcpy(upCopyString.get(), rString.c_str(), memorySize);

            // 連想配列から順に解析
            JsonObject object;
            s_ParseObject(&object, upCopyString.get());
        
            return object;
        }


        /*************************************************************//**
         *
         *  @brief  ファイルからJSONオブジェクトを作成する
         *  @param  ファイルパス
         *  @return JSONオブジェクト
         *
         ****************************************************************/
        static JsonObject s_CreateFromFile(const String& rFilePath)
        {
            // ファイルを開く
            std::ifstream inFile(rFilePath, std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_JsonObject::s_CreateFromFile ] : 入力ファイルを開くのに失敗しました。");
            }

            // 開始と終了のイテレータをストリームから生成
            std::istreambuf_iterator<char> beginIterator(inFile);
            std::istreambuf_iterator<char> lastIterator;

            // ファイルを丸ごと文字列として読み込む
            String string(beginIterator, lastIterator);

            // 文字列からJSONオブジェクトを作成
            return s_CreateFromString(string);
        }


        /*************************************************************//**
         *
         *  @brief  JSONファイルを書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  ファイルパス
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteToJsonFile(const JsonObject& rJsonObject, const String& rFilePath)
        {
            // ファイルを開く
            std::ofstream outFile(rFilePath);

            if (outFile.fail() == true)
            {
                throw std::runtime_error("[ C_JsonObject::s_WriteToJsonFile ] : 出力ファイルを開くのに失敗しました。");
            }

            // 種類別に書き込み
            s_WriteTypeDistinguish(rJsonObject, &outFile);
        }

#pragma endregion

#pragma region public演算子のオーバーロード
        
        /*************************************************************//**
         *
         *  @brief  代入演算子のオーバーロード
         *  @param  JSONオブジェクト
         *  @return なし
         *
         ****************************************************************/
        void operator=(const JsonObject& rOther) = delete;


        /*************************************************************//**
         *
         *  @brief  代入演算子のオーバーロード( ムーブ )
         *  @param  JSONオブジェクト
         *  @return なし
         *
         ****************************************************************/
        void operator=(JsonObject&& rrOther)
        {
            // 値を解放
            if (pValue_) DataFree();

            // 各データを設定
            key_ = rrOther.key_;
			pValue_ = rrOther.pValue_;
			dataType_ = rrOther.dataType_;
			rrOther.pValue_ = nullptr;
		}


        /*************************************************************//**
         *
         *  @brief  代入演算子のオーバーロード
         *  @param  整数
         *  @return なし
         *
         ****************************************************************/
        void operator=(Integer value)
        {
            DataAlloc<ecDataType::TYPE_INTEGER>();
            Assign(value);
        }


        /*************************************************************//**
         *
         *  @brief  代入演算子のオーバーロード
         *  @param  実数
         *  @return なし
         *
         ****************************************************************/
        void operator=(Real value)
        {
            DataAlloc<ecDataType::TYPE_REAL>();
            Assign(value);
        }


        /*************************************************************//**
         *
         *  @brief  代入演算子のオーバーロード
         *  @param  文字列
         *  @return なし
         *
         ****************************************************************/
        void operator=(const String& rString)
        {
            DataAlloc<ecDataType::TYPE_STRING>();
            Construct<String>(pValue_, rString);
        }


        /*************************************************************//**
         *
         *  @brief  代入演算子のオーバーロード
         *  @param  bool値
         *  @return なし
         *
         ****************************************************************/
        void operator=(Boolean value)
        {
            DataAlloc<ecDataType::TYPE_BOOLEAN>();
            Assign(value);
        }


        /*************************************************************//**
         *
         *  @brief  添え字演算子のオーバーロード
         *  @param  インデックス
         *  @return JSONオブジェクト
         *
         ****************************************************************/
        JsonObject& operator[](std::size_t index)
        {
            // 配列操作のオブジェクトを取得
            C_ArrayOperation arrayOperation = GetArrayOperation();

            // メモリを確保
            if (DataAlloc<ecDataType::TYPE_ARRAY>() == true)
            {
                Construct<Array>(pValue_);
                arrayOperation.Reserve(16);
            }

            return arrayOperation[index];
        }


        /*************************************************************//**
         *
         *  @brief  添え字演算子のオーバーロード
         *  @param  キー
         *  @return JSONオブジェクト
         *
         ****************************************************************/
        JsonObject& operator[](const String& rKey)
        {
            // 連想配列操作のオブジェクトを取得
            C_ObjectOperation objectOperation = GetObjectOperation();
            
            // メモリを確保
            if (DataAlloc<ecDataType::TYPE_OBJECT>() == true) Construct<Object>(pValue_);

            // キーから要素を検索し、見つからない場合は要素を挿入
            JsonObject* pJsonObject = objectOperation.Find(rKey);
            if (pJsonObject == nullptr) pJsonObject = objectOperation.Insert(rKey);

            return *pJsonObject;
        }

#pragma endregion

    private:

#pragma region メンバ変数

        void* pValue_ = nullptr;                                                            ///< @brief 値
        String key_;                                                                        ///< @brief キー
        ecDataType dataType_ = ecDataType::TYPE_NULL;                                       ///< @brief データの種類
        AllocateObject allocateObject_;                                                     ///< @brief メモリ割り当てに用いるオブジェクト
        FreeObject freeObject_;                                                             ///< @brief メモリ解放に用いるオブジェクト

#pragma endregion

#pragma region privateメンバ関数

        /*************************************************************//**
         *
         *  @brief  指定した種類のメモリを確保する
         *  @param  なし
         *  @return 確保した場合      ：true
         *  @return 確保されていた場合：false
         *
         ****************************************************************/
        template<ecDataType dataType>
        bool DataAlloc()
        {
            // 型が不一致の場合、メモリを再確保
            if (TypeEqual(dataType) == false)
            {
                // メモリを確保
                if (Alloc(S_TypeSize<dataType>::s_size) == false)
                {
                    DataFree();
                    Alloc(S_TypeSize<dataType>::s_size);
                }

                // データの種類を設定
                dataType_ = dataType;

                return true;
            }

            return false;
        }


        /*************************************************************//**
         *
         *  @brief  サイズ分だけメモリを確保する
         *  @param  メモリのサイズ
         *  @return 確保した場合      ：true
         *  @return 確保されていた場合：false
         *
         ****************************************************************/
        bool Alloc(std::size_t size)
        {
            if (pValue_ == nullptr)
            {
                pValue_ = allocateObject_(size);

                return true;
            }

            return false;
        }


        /*************************************************************//**
         *
         *  @brief  メモリを確保する
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void DataFree()
        {
            // 文字列・配列・連想配列の場合はデストラクタを呼ぶ
            if (pValue_)
            {
                switch (dataType_)
                {
                case ecDataType::TYPE_STRING:

                    Destruct<String>(pValue_);

                    break;
                case ecDataType::TYPE_ARRAY:

                    Destruct<Array>(pValue_);

                    break;
                case ecDataType::TYPE_OBJECT:

                    Destruct<Object>(pValue_);

                    break;
                }

                // メモリを解放
                freeObject_(pValue_);
                pValue_ = nullptr;
            }
        }


        /*************************************************************//**
         *
         *  @brief  データの種類を比較する
         *  @param  データの種類
         *  @return 種類が文字列以外で同じ場合：true
         *  @return 種類が違う場合            ：false
         *
         ****************************************************************/
        bool TypeEqual(ecDataType dataType)
        {
            if (dataType_ != ecDataType::TYPE_STRING && dataType_ == dataType) return true;

            return false;
        }


        /*************************************************************//**
         *
         *  @brief  種類の名前を取得する
         *  @param  データの種類
         *  @return 種類の名前
         *
         ****************************************************************/
        const char* GetTypeName(ecDataType dataType)
        {
            switch (dataType_)
            {
            case ecDataType::TYPE_INTEGER:

                return "Integer";

                break;
            case ecDataType::TYPE_REAL:

                return "Real";

                break;
            case ecDataType::TYPE_BOOLEAN:

                return "Boolean";

                break;
            case ecDataType::TYPE_STRING:

                return "String";

                break;
            case ecDataType::TYPE_ARRAY:

                return "Array";

                break;
            case ecDataType::TYPE_OBJECT:

                return "Object";

                break;
            case ecDataType::TYPE_NULL:

                return "Null";

                break;
            }

            return "Unknown";
        }


        /*************************************************************//**
         *
         *  @brief  値を代入する
         *  @param  整数
         *  @return なし
         *
         ****************************************************************/
        void Assign(Integer value)
        {
            auto pIntegerValue = IntegerCast();
            *pIntegerValue = value;
        }


        /*************************************************************//**
         *
         *  @brief  値を代入する
         *  @param  実数
         *  @return なし
         *
         ****************************************************************/
        void Assign(Real value)
        {
            auto pRealValue = RealCast();
            *pRealValue = value;
        }


        /*************************************************************//**
         *
         *  @brief  値を代入する
         *  @param  ブール値
         *  @return なし
         *
         ****************************************************************/
        void Assign(Boolean value)
        {
            auto pBooleanValue = BooleanCast();
            *pBooleanValue = value;
        }


        /*************************************************************//**
         *
         *  @brief  明示的コンストラクタの呼び出しを行う
         *  @param  ポインタ
         *  @param  生成する型の引き数
         *  @return なし
         *
         ****************************************************************/
        template<typename T, typename ...Args>
        void Construct(void* pPointer, Args&&... args)
        {
           ::new (pPointer)T(std::forward<Args>(args)...);
        }


        /*************************************************************//**
         *
         *  @brief  明示的デストラクタの呼び出しを行う
         *  @param  ポインタ
         *  @return なし
         *
         ****************************************************************/
        template<typename T>
        void Destruct(void* pPointer)
        {
            reinterpret_cast<T*>(pPointer)->~T();
        }


        /*************************************************************//**
         *
         *  @brief  Character型へキャストを行う
         *  @param  なし
         *  @return Character型の値
         *
         ****************************************************************/
        Character* CharacterCast() const
        {
            return reinterpret_cast<Character*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Integer型へキャストを行う
         *  @param  なし
         *  @return Integer型の値
         *
         ****************************************************************/
        Integer* IntegerCast() const
        {
            return reinterpret_cast<Integer*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Real型へキャストを行う
         *  @param  なし
         *  @return Real型の値
         *
         ****************************************************************/
        Real* RealCast() const
        {
            return reinterpret_cast<Real*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Boolean型へキャストを行う
         *  @param  なし
         *  @return Boolean型の値
         *
         ****************************************************************/
        Boolean* BooleanCast() const
        {
            return reinterpret_cast<Boolean*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  String型へキャストを行う
         *  @param  なし
         *  @return String型の値
         *
         ****************************************************************/
        String* StringCast() const
        {
            return reinterpret_cast<String*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Array型へキャストを行う
         *  @param  なし
         *  @return Array型の値
         *
         ****************************************************************/
        Array* ArrayCast() const
        {
            return reinterpret_cast<Array*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Object型へキャストを行う
         *  @param  なし
         *  @return Object型の値
         *
         ****************************************************************/
        Object* ObjectCast() const
        {
            return reinterpret_cast<Object*>(pValue_);
        }

#pragma endregion

#pragma region private静的メンバ関数

        /*************************************************************//**
         *
         *  @brief  連想配列を解析する
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static char* s_ParseObject(JsonObject* pJsonObject, char* pString)
        {
            // ループ終了フラグ
            bool loopFinishFlag = false;

            // 中括弧( 開 )の場合は文字を一つ進め、Jsonオブジェクトをオブジェクトとして構築
            if (*pString == '{')
            {
                ++pString;
                pJsonObject->RemakeAsObject();
            }

            do
            {
                switch (*pString)
                {
                /* 中括弧( 開 ) */
                case '{':

                    // 再帰的に解析を行う
                    pString = s_ParseObject(pJsonObject, pString);

                    break;
                /* 中括弧( 閉 ) */
                case '}':

                    ++pString;
                    loopFinishFlag = true;

                    break;
                /* ダブルクォーテーション( データ ) */
                case '\"':
                {
                    // 値の名前を取得
                    auto valueNameAndNextString = s_GetValueName(pString);

                    String valueName = std::get<0>(valueNameAndNextString);
                    pString = std::get<1>(valueNameAndNextString);

                    // 値を割り当てる
                    pString = s_AssignValue(&((*pJsonObject)[valueName]), pString);
                }
                    break;
                /* その他 */
                default:

                    ++pString;

                    break;
                }
            } while (loopFinishFlag == false);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  値の名前を取得する
         *  @param  文字列
         *  @return 値の名前と次の文字列
         *
         ****************************************************************/
        static std::tuple<String, char*> s_GetValueName(char* pString)
        {
            // 文字のインデックス
            int32_t stringIndex = 0;

            // 1つ目のダブルクォーテーションはインデックスを1つ進める
            if (pString[stringIndex] == '\"') ++stringIndex;

            // 値の名前と文字の数
            char valueName[256] = {};
            int32_t characterCount = 0;

            // 2つ目のダブルクォーテーションが来るまで値の名前として文字を取得
            while (pString[stringIndex] != '\"')
            {
                valueName[characterCount] = pString[stringIndex];

                ++stringIndex;
                ++characterCount;
            }

            // 文字名と文字列を返す
            return std::make_tuple(String(valueName), pString + stringIndex + 1);
        }


        /*************************************************************//**
         *
         *  @brief  値の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 値の名前と次の文字列
         *
         ****************************************************************/
        static char* s_AssignValue(JsonObject* pJsonObject, char* pString)
        {
            // ループ終了フラグ
            bool loopFinishFlag = false;

            do
            {
                switch (*pString)
                {
                /* 中括弧( 開 ) */
                case '{':

                    pString = s_ParseObject(pJsonObject, pString);
                    loopFinishFlag = true;

                    break;
                /* 中括弧( 閉 ) */
                case '}':

                    ++pString;
                    loopFinishFlag = true;

                    break;
                /* 中括弧( 閉 ) */
                case '\"':

                    pString = s_AssignString(pJsonObject, pString);
                    loopFinishFlag = true;

                    break;
                /* 角括弧( 開 ) */
                case '[':

                    pString = s_AssignArray(pJsonObject, pString);
                    loopFinishFlag = true;

                    break;
                /* その他 */
                default:
                {
                    // 数字の割り当てを行う
                    // 割り当てられなかった場合は文字を1つ進めてループ
                    auto resultFlagAndNextString = s_AssignNumber(pJsonObject, pString);

                    if (std::get<0>(resultFlagAndNextString) == true)
                    {
                        pString = std::get<1>(resultFlagAndNextString);
                        loopFinishFlag = true;
                    }
                    else
                    {
                        ++pString;
                    }
                }
                    break;
                }

            } while (loopFinishFlag == false);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  配列の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static char* s_AssignArray(JsonObject* pJsonObject, char* pString)
        {
            // 角括弧( 開 )の場合は文字を1つ進め、JSONオブジェクトを配列として構築
            if (*pString == '[')
            {
                ++pString;
                pJsonObject->RemakeAsArray();
            }

            // JSONオブジェクトのインデックス
            int32_t jsonObjectIndex = 0;

            // ループ終了のフラグ
            bool loopFinishFlag = false;

            do
            {
                switch (*pString)
                {
                /* 角括弧( 開 ) */
                case '[':

                    pString = s_AssignArray(&((*pJsonObject)[jsonObjectIndex]), pString);

                    break;
                /* 角括弧( 閉 ) */
                case ']':

                    ++pString;
                    loopFinishFlag = true;

                    break;
                /* カンマ */
                case ',':

                    ++jsonObjectIndex;
                    ++pString;

                    break;
                /* 中括弧( 開 ) */
                case '{':

                    pString = s_ParseObject(&((*pJsonObject)[jsonObjectIndex]), pString);

                    break;
                /* ダブルクォーテーション */
                case '\"':

                    pString = s_AssignString(&((*pJsonObject)[jsonObjectIndex]), pString);

                    break;
                /* その他 */
                default:
                {
                    // 数字の割り当てを行う
                    // 割り当てられなかった場合は文字を1つ進めてループ
                    auto resultFlagAndString = s_AssignNumber(&((*pJsonObject)[jsonObjectIndex]), pString);

                    if (std::get<0>(resultFlagAndString) == true)
                    {
                        pString = std::get<1>(resultFlagAndString);
                    }
                    else
                    {
                        ++pString;
                    }
                }
                    break;
                }

            } while (loopFinishFlag == false);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  文字列の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static char* s_AssignString(JsonObject* pJsonObject, char* pString)
        {
            auto valueNameAndNextString = s_GetValueName(pString);

            *pJsonObject = std::get<0>(valueNameAndNextString);
            pString = std::get<1>(valueNameAndNextString);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  数字の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static std::tuple<bool, char*> s_AssignNumber(JsonObject* pJsonObject, char* pString)
        {
            bool resultFlag = false;

            /* 数値の場合 */
            if (*pString >= '0' && *pString <= '9')
            {
                pString = s_AssignIntegerOrReal(pJsonObject, pString);
                resultFlag = true;
            }
            /* bool値の場合 */
            else if (*pString == 't' || *pString == 'f')
            {
                pString = s_AssignBoolean(pJsonObject, pString);
                resultFlag = true;
            }
            /* null値の場合 */
            else if (*pString == 'n')
            {
                pString = s_AssignNull(pJsonObject, pString);
                resultFlag = true;
            }

            return std::make_tuple(resultFlag, pString);
        }


        /*************************************************************//**
         *
         *  @brief  整数または実数の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static char* s_AssignIntegerOrReal(JsonObject* pJsonObject, char* pString)
        {
            // 値の文字列
            char valueString[256] = {};
            
            // 実数か判断するフラグ
            bool realFlag = false;

            // 値の文字列のインデックス
            int valueStringIndex = 0;

            // 値の文字列を取得
            while (true)
            {
                if (pString[valueStringIndex] == ',' || pString[valueStringIndex] == '}' || pString[valueStringIndex] == ']')
                {
                    break;
                }
                else if ((pString[valueStringIndex] >= '0' && pString[valueStringIndex] <= '9') || pString[valueStringIndex] == '.')
                {
                    valueString[valueStringIndex] = pString[valueStringIndex];

                    if (pString[valueStringIndex] == '.') realFlag = true;
                }

                ++valueStringIndex;
            }

            // 文字列を数値化
            if (realFlag == true)
            {
                *pJsonObject = std::stod(valueString);
            }
            else
            {
                *pJsonObject = std::stoi(valueString);
            }
            
            return pString + valueStringIndex;
        }


        /*************************************************************//**
         *
         *  @brief  ブール値の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static char* s_AssignBoolean(JsonObject* pJsonObject, char* pString)
        {
            // 文字数
            int32_t stringCount = 0;

            /* trueの場合 */
            if (*pString == 't')
            {
                *pJsonObject = true;
                stringCount = 4;
            }
            /* falseの場合 */
            else
            {
                *pJsonObject = false;
                stringCount = 5;
            }

            return pString + stringCount;
        }


        /*************************************************************//**
         *
         *  @brief  null値の割り当てを行う
         *  @param  JSONオブジェクト
         *  @param  文字列
         *  @return 次の文字列
         *
         ****************************************************************/
        static char* s_AssignNull(JsonObject* pJsonObject, char* pString)
        {
            return pString + 4;
        }


        /*************************************************************//**
         *
         *  @brief  種類別に書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @param  タブが既に挿入済みか判断するフラグ
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteTypeDistinguish(const JsonObject& rJsonObject, std::ofstream* pOutFile, bool tabAlreadyInsertFlag = false)
        {
            switch (rJsonObject.dataType_)
            {
            case ecDataType::TYPE_INTEGER:

                s_WriteInteger(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_REAL:

                s_WriteReal(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_BOOLEAN:

                s_WriteBoolean(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_STRING:

                s_WriteString(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_ARRAY:

                s_WriteArray(rJsonObject, pOutFile, tabAlreadyInsertFlag);

                break;
            case ecDataType::TYPE_OBJECT:

                s_WriteObject(rJsonObject, pOutFile, tabAlreadyInsertFlag);

                break;
            case ecDataType::TYPE_NULL:

                s_WriteNull(rJsonObject, pOutFile);

                break;
            }
        }


        /*************************************************************//**
         *
         *  @brief  整数の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteInteger(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";

            *pOutFile << rJsonObject.GetValue<Integer>();
        }


        /*************************************************************//**
         *
         *  @brief  実数の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteReal(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";
            
            *pOutFile << std::fixed << std::setprecision(6) << rJsonObject.GetValue<Real>();
        }


        /*************************************************************//**
         *
         *  @brief  bool値の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteBoolean(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";

            rJsonObject.GetValue<Boolean>() == true ? *pOutFile << "true" : *pOutFile << "false";
        }


        /*************************************************************//**
         *
         *  @brief  文字列の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteString(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";
            

            *pOutFile << "\"" << rJsonObject.GetValue<String>() << "\"";
        }


        /*************************************************************//**
         *
         *  @brief  配列の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @param  タブが既に挿入済みか判断するフラグ
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteArray(const JsonObject& rJsonObject, std::ofstream* pOutFile, bool tabAlreadyInsertFlag)
        {
            // キーを取得
            String key = rJsonObject.GetKey();

            // キーと角括弧( 開 )を書き込み
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : \n";
            if (tabAlreadyInsertFlag == false) s_WriteTab(pOutFile);
            *pOutFile << "[\n";

            // 配列を取得
            auto& rArray = *rJsonObject.ArrayCast();

            // 配列のイテレータを取得
            auto iterator = rArray.begin();

            // ループの終了を判断するフラグ
            bool loopFinishFlag = !(iterator != rArray.end());

            // タブを1増加
            s_WriteTab(nullptr, 1);

            while (loopFinishFlag == false)
            {
                // タブを挿入
                s_WriteTab(pOutFile);

                // 種類別に書き込み
                s_WriteTypeDistinguish(*iterator, pOutFile, true);
                ++iterator;

                // ループの終了を判断
                if (iterator != rArray.end())
                {
                    *pOutFile << ",\n";
                }
                else
                {
                    loopFinishFlag = true;
                }
            }

            // タブを1減少
            s_WriteTab(nullptr, -1);

            // 改行し角括弧( 閉 )を書き込み
            *pOutFile << "\n";
            s_WriteTab(pOutFile);
            *pOutFile << "]";
        }


        /*************************************************************//**
         *
         *  @brief  連想配列の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @param  タブが既に挿入済みか判断するフラグ
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteObject(const JsonObject& rJsonObject, std::ofstream* pOutFile, bool tabAlreadyInsertFlag)
        {
            // キーを取得
            String key = rJsonObject.GetKey();

            // キーと中括弧( 開 )を書き込み
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : \n";
            if (tabAlreadyInsertFlag == false) s_WriteTab(pOutFile);
            *pOutFile << "{\n";

            // 連想配列を取得
            auto& rObject = *(rJsonObject.ObjectCast());

            // 連想配列のイテレータを取得
            auto iterator = rObject.begin();

            // ループの終了を判断するフラグ
            bool loopFinishFlag = !(iterator != rObject.end());

            // タブを1増加
            s_WriteTab(nullptr, 1);

            while (loopFinishFlag == false)
            {
                // タブを挿入
                s_WriteTab(pOutFile);

                // 種類別に書き込み
                s_WriteTypeDistinguish(iterator->second, pOutFile);
                ++iterator;

                // ループの終了を判断
                if (iterator != rObject.end())
                {
                    *pOutFile << ",\n";
                }
                else
                {
                    loopFinishFlag = true;
                }
            }

            // タブを1減少
            s_WriteTab(nullptr, -1);

            // 中括弧( 閉 )を書き込み
            *pOutFile << "\n";
            s_WriteTab(pOutFile);
            *pOutFile << "}";
        }


        /*************************************************************//**
         *
         *  @brief  null値の書き込みを行う
         *  @param  JSONオブジェクト
         *  @param  出力ストリーム
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteNull(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            auto key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";
            *pOutFile << "null";
        }


        /*************************************************************//**
         *
         *  @brief  タブの書き込みを行う
         *  @param  出力ストリーム
         *  @param  加えるタブ数
         *  @return なし
         *
         ****************************************************************/
        static void s_WriteTab(std::ofstream* pOutFile, int32_t addTab = 0)
        {
            // タブ数
            static int32_t s_tabCount = 0;
            
            // 合計数にタブ数を加算
            s_tabCount += addTab;
            assert(s_tabCount >= 0);

            if (pOutFile)
            {
                for (int32_t i = 0; i < s_tabCount; ++i)
                {
#ifdef JSON_ENABLE_INSERT_TAB

                    *pOutFile << "\t";

#else

                    *pOutFile << "    ";

#endif
                }
            }
        }

#pragma endregion

    };

    /* 別名 */
    using JsonObject = C_JsonObject<>;                                                      // JsonObject型を省略
    using Character = C_JsonObject<>::Character;                                            // Character型を省略
    using Integer = C_JsonObject<>::Integer;                                                // Integer型を省略
    using Real = C_JsonObject<>::Real;                                                      // Real型を省略
    using Boolean = C_JsonObject<>::Boolean;                                                // Boolean型を省略
    using String = C_JsonObject<>::String;                                                  // String型を省略
    using Array = C_JsonObject<>::Array;                                                    // Array型を省略
    using Object = C_JsonObject<>::Object;                                                  // Object型を省略
}
