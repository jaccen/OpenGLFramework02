/* ヘッダファイル */
#include "ObjLoader.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include "../../../Common/CommonHelper.h"
#include "../../../Path/PathAnalizer.h"
#include <fstream>
#include <sstream>
#include <deque>
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief モデル
//! @brief モデル関連の名前空間
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief OBJ
    //! @brief OBJ関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace OBJ
    {
        //-------------------------------------------------------------
        //!
        //! @brief OBJローダーインプリメント
        //! @brief OBJローダーのプライベート情報の実装
        //!
        //-------------------------------------------------------------
        class C_ObjLoader::C_ObjLoaderImpl
        {
        public:
            C_ObjLoaderImpl();                                                                                  // コンストラクタ
            ~C_ObjLoaderImpl();                                                                                 // デストラクタ
            void Load(const std::string& rFilePath);                                                            // ロード処理
            void Release();                                                                                     // 解放処理
            const S_Mesh& GetMesh() const;                                                                      // メッシュを取得
            uint32_t GetMaterialCount() const;                                                                  // マテリアル数を取得
            int32_t GetMaterialIndex(const std::string& rName) const;                                           // マテリアルのIDを取得
            const S_Material& GetMaterial(int32_t id) const;                                                    // マテリアルを取得
        private:
            S_Mesh mesh_;                                                                                       ///< @brief メッシュ
            std::deque<S_Material> materials_;                                                                  ///< @brief マテリアル
            std::unordered_map<std::string, int16_t> materialIdDictionary_;                                     ///< @brief マテリアルIDの辞書
            int32_t polygonCount_ = 0;                                                                          ///< @brief ポリゴンの数
            int32_t vertexCount_ = 0;                                                                           ///< @brief 頂点数

            void ParseObjFile(const std::string& rFilePath);                                                    // OBJファイルの解析
            void ParseMtlFile(const std::string& rFilePath);                                                    // MTLファイルの解析
            void AddPosition(std::stringstream* pStringStream, std::vector<Vector3>* pPositions);               // 頂点座標を追加
            void AddNormal(std::stringstream* pStringStream, std::vector<Vector3>* pNormals);                   // 法線ベクトルを追加
            void AddTextureCoord(std::stringstream* pStringStream, std::vector<Vector2>* pTextureCoords);       // テクスチャ座標を追加
            void AddVertex(std::stringstream* pStringStream,                                                    // 頂点を追加     
                           const std::vector<Vector3>& rPositions,
                           const std::vector<Vector3>& rNormals,
                           const std::vector<Vector2>& rTextureCoords,
                           std::vector<S_Vertex>* pVertices,
                           std::vector<uint16_t>* pIndices);
            void SetColor(std::stringstream* pStringStream, Vector3* pColor);                                   // 色を設定
        };


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ObjLoader::C_ObjLoaderImpl::C_ObjLoaderImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ObjLoader::C_ObjLoaderImpl::~C_ObjLoaderImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ロード処理を行う
         *  @param  ファイルパス
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::Load(const std::string& rFilePath)
        {
            // OBJファイルを解析
            ParseObjFile(rFilePath);
        }


        /*************************************************************//**
         *
         *  @brief  解放処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::Release()
        {
            mesh_.vertices_.clear();
            mesh_.indices_.clear();
            mesh_.materialName_.clear();

            materials_.clear();
            materialIdDictionary_.clear();

            polygonCount_ = 0;
            vertexCount_ = 0;
        }


        /*************************************************************//**
         *
         *  @brief  メッシュを取得する
         *  @param  なし
         *  @return メッシュ
         *
         ****************************************************************/
        const S_Mesh& C_ObjLoader::C_ObjLoaderImpl::GetMesh() const
        {
            return mesh_;
        }


        /*************************************************************//**
         *
         *  @brief  マテリアル数を取得する
         *  @param  なし
         *  @return マテリアル数
         *
         ****************************************************************/
        uint32_t C_ObjLoader::C_ObjLoaderImpl::GetMaterialCount() const
        {
            return materials_.size();
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルインデックスを取得する
         *  @param  マテリアル名
         *  @return マテリアルインデックス
         *
         ****************************************************************/
        int32_t C_ObjLoader::C_ObjLoaderImpl::GetMaterialIndex(const std::string& rName) const
        {
            return materialIdDictionary_.at(rName);
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルを取得する
         *  @param  マテリアルインデックス
         *  @return マテリアル
         *
         ****************************************************************/
        const S_Material& C_ObjLoader::C_ObjLoaderImpl::GetMaterial(int32_t index) const
        {
            return materials_.at(index);
        }


        /*************************************************************//**
         *
         *  @brief  OBJファイルの解析を行う
         *  @param  ファイルパス
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::ParseObjFile(const std::string& rFilePath)
        {
            // ファイルを開く
            std::ifstream inFile(rFilePath, std::ifstream::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ObjLoaderImpl::LoadObjFile ] : OBJファイルを開くのに失敗しました。");
            }

            // 座標・法線ベクトル・テクスチャ座標
            std::vector<Vector3> positions;
            std::vector<Vector3> normals;
            std::vector<Vector2> textureCoords;
            std::vector<S_Vertex> vertices;
            std::vector<uint16_t> indices;

            // 各メモリを確保
            const int32_t RESERVE_NUMBER = 100000;

            mesh_.vertices_.reserve(RESERVE_NUMBER);
            positions.reserve(RESERVE_NUMBER);
            normals.reserve(RESERVE_NUMBER);
            textureCoords.reserve(RESERVE_NUMBER);

            // 1行分のデータを取得し、文字列ストリームに格納
            std::string lineData;
            std::getline(inFile, lineData);
            lineData = Common::C_CommonHelper::s_TrimString(lineData);
            std::stringstream stringStream(lineData);

            // 判別用文字
            std::string distinctionCharacter;

            // ファイルの最後の行が来るまでループ
            while (inFile.eof() == false)
            {
                // 文字列が存在し、それがコメントでない場合は各データを設定
                if (lineData.length() > 0 && lineData.at(0) != '#')
                {
                    // 文字列ストリームから判別用の文字を取得
                    stringStream >> distinctionCharacter;

                    /* 座標 */
                    if (distinctionCharacter == "v")
                    {
                        AddPosition(&stringStream, &positions);
                    }
                    /* テクスチャ座標 */
                    else if (distinctionCharacter == "vt")
                    {
                        AddTextureCoord(&stringStream, &textureCoords);
                    }
                    /* 法線ベクトル */
                    else if (distinctionCharacter == "vn")
                    {
                        AddNormal(&stringStream, &normals);
                    }
                    /* ポリゴン( 面 ) */
                    else if (distinctionCharacter == "f")
                    {
                        AddVertex(&stringStream,
                                  positions,
                                  normals,
                                  textureCoords,
                                  &vertices,
                                  &indices);
                    }
                    /* マテリアルファイル */
                    else if (distinctionCharacter == "mtllib")
                    {
                        // マテリアルファイル名を取得
                        std::string materialFileName;
                        stringStream >> materialFileName;
                        materialFileName = Path::C_PathAnalizer::s_GetFileName(materialFileName);

                        // ディレクトリ名を取得し、マテリアルファイル名と連結
                        std::string directoryName = Path::C_PathAnalizer::s_GetDirectoryName(rFilePath);
                        std::string materialFilePath = directoryName + materialFileName;

                        // MTLファイルを解析
                        ParseMtlFile(materialFileName);
                    }

                }

                // 文字列ストリームのバッファをクリア
                stringStream.str("");
                stringStream.clear(std::stringstream::goodbit);

                // 1行分のデータを読み込み、文字列ストリームに格納
                std::getline(inFile, lineData);
                lineData = Common::C_CommonHelper::s_TrimString(lineData);
                stringStream << lineData;
            }

            // メッシュの頂点をインデックスを取得
            auto& rMeshVertices = mesh_.vertices_;
            rMeshVertices.reserve(vertices.size());

            size_t indicesCount = indices.size();
            auto& rMeshIndices = mesh_.indices_;
            rMeshIndices.reserve(indicesCount);

            for (size_t i = 0; i < indicesCount; ++i)
            {
                auto& rVertex = vertices[indices[i]];

                // 重複している頂点を検索し、検索結果により頂点とインデックスを割り振る
                auto iterator = std::find(rMeshVertices.begin(), rMeshVertices.end(), rVertex);

                /* 重複していない */
                if (iterator == rMeshVertices.end())
                {
                    rMeshIndices.push_back(rMeshVertices.size());
                    rMeshVertices.push_back(rVertex);
                }
                /* 重複している */
                else
                {
                    size_t index = std::distance(rMeshVertices.begin(), iterator);
                    rMeshIndices.push_back(index);
                }
            }

            // 頂点の余分なメモリ領域をなくす
            rMeshVertices.shrink_to_fit();
        }


        /*************************************************************//**
         *
         *  @brief  MTLファイルの解析を行う
         *  @param  ファイルパス
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::ParseMtlFile(const std::string& rFilePath)
        {
            // ファイルを開く
            std::ifstream inFile(rFilePath);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ObjLoaderImpl::ParseMtlFile ] : MTLファイルを開くのに失敗しました。");
            }

            // 一行分のデータを取得し、文字列ストリームに格納
            std::string lineData;
            std::getline(inFile, lineData);
            lineData = Common::C_CommonHelper::s_TrimString(lineData);
            std::stringstream stringStream(lineData);

            // 判別用文字
            std::string distinctionCharacter;

            // マテリアルのインデックス
            int materialIndex = -1;

            // ファイルの最後の行が来るまでループ
            while (inFile.eof() == false)
            {
                // 文字列が存在し、それがコメントでない場合は各データを設定
                if (lineData.length() > 0 && lineData.at(0) != '#')
                {
                    // 文字列ストリームから判別用の文字を取得
                    stringStream >> distinctionCharacter;

                    /* 新しいマテリアル */
                    if (distinctionCharacter == "newmtl")
                    {
                        // マテリアルのインデックス1つ増加
                        ++materialIndex;

                        // マテリアルを1つ追加し、マテリアル名を取得
                        materials_.emplace_back();
                        stringStream >> materials_[materialIndex].name_;

                        // マテリアル名を辞書に登録
                        materialIdDictionary_.emplace(materials_[materialIndex].name_, materialIndex);

                        // 一番最初のマテリアルをメッシュのマテリアルとして名前を設定
                        if (mesh_.materialName_.empty() == true) mesh_.materialName_ = materials_[materialIndex].name_;
                    }
                    /* アンビエントカラー */
                    else if (distinctionCharacter == "Ka")
                    {
                        SetColor(&stringStream, &materials_[materialIndex].ambient_);
                    }
                    /* ディフューズカラー */
                    else if (distinctionCharacter == "Kd")
                    {
                        SetColor(&stringStream, &materials_[materialIndex].diffuse_);
                    }
                    /* スペキュラーカラー */
                    else if (distinctionCharacter == "Ks")
                    {
                        SetColor(&stringStream, &materials_[materialIndex].specular_);
                    }
                    /* 不透明度 */
                    else if (distinctionCharacter == "d" || distinctionCharacter == "Tr")
                    {
                        stringStream >> materials_[materialIndex].opacity_;
                    }
                    /* 光沢 */
                    else if (distinctionCharacter == "Ns")
                    {
                        stringStream >> materials_[materialIndex].shininess_;
                    }
                    /* アンビエントマップ */
                    else if (distinctionCharacter == "map_Ka")
                    {
                        stringStream >> materials_[materialIndex].ambientTextureFileName_;
                    }
                    /* ディフューズマップ */
                    else if (distinctionCharacter == "map_Kd")
                    {
                        stringStream >> materials_[materialIndex].diffuseTextureFileName_;
                    }
                    /* スペキュラーマップ */
                    else if (distinctionCharacter == "map_Ks")
                    {
                        stringStream >> materials_[materialIndex].specularTextureFileName_;
                    }
                }

                // 文字列ストリームのバッファをクリア
                stringStream.str("");
                stringStream.clear(std::stringstream::goodbit);

                // 1行分のデータを読み込み、文字列ストリームに格納
                std::getline(inFile, lineData);
                lineData = Common::C_CommonHelper::s_TrimString(lineData);
                stringStream << lineData;
            }
        }


        /*************************************************************//**
         *
         *  @brief  座標を追加する
         *  @param  文字列ストリーム
         *  @param  座標
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::AddPosition(std::stringstream* pStringStream, std::vector<Vector3>* pPositions)
        {
            Vector3 tempPosition;
            (*pStringStream) >> tempPosition.x_ >> tempPosition.y_ >> tempPosition.z_;

            (*pPositions).push_back(tempPosition);
        }


        /*************************************************************//**
         *
         *  @brief  法線ベクトルを追加する
         *  @param  文字列ストリーム
         *  @param  法線ベクトル
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::AddNormal(std::stringstream* pStringStream, std::vector<Vector3>* pNormals)
        {
            Vector3 tempNormal;
            (*pStringStream) >> tempNormal.x_ >> tempNormal.y_ >> tempNormal.z_;

            (*pNormals).push_back(tempNormal);
        }


        /*************************************************************//**
         *
         *  @brief  テクスチャ座標を追加する
         *  @param  文字列ストリーム
         *  @param  テクスチャ座標
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::AddTextureCoord(std::stringstream* pStringStream, std::vector<Vector2>* pTextureCoords)
        {
            Vector2 tempTextureCoord;
            (*pStringStream) >> tempTextureCoord.x_ >> tempTextureCoord.y_;

            tempTextureCoord.y_ = 1.0f - tempTextureCoord.y_;
            (*pTextureCoords).push_back(tempTextureCoord);
        }


        /*************************************************************//**
         *
         *  @brief  頂点を追加する
         *  @param  文字列ストリーム
         *  @param  座標
         *  @param  法線ベクトル
         *  @param  テクスチャ座標
         *  @param  頂点
         *  @param  インデックス
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::AddVertex(std::stringstream* pStringStream,
                                                     const std::vector<Vector3>& rPositions,
                                                     const std::vector<Vector3>& rNormals,
                                                     const std::vector<Vector2>& rTextureCoords,
                                                     std::vector<S_Vertex>* pVertices,
                                                     std::vector<uint16_t>* pIndices)
        {
            // ポリゴンの頂点数
            int32_t polygonVertexCount = 0;

            // 仮の頂点
            S_Vertex tempVertex;

            // 頂点データ
            std::string vertexData;

            // '/'の入っている位置を格納する変数
            size_t firstSlashLocation = 0, secondSlashLocation = 0;

            // 各インデックス
            int32_t positionIndex = 0, textureCoordIndex = 0, normalIndex = 0;

            // インデックスの補正値
            const int32_t INDEX_CORRECTION = 1;

            do
            {
                // 頂点データを取得
                (*pStringStream) >> vertexData;

                // 1つ目の'/'の位置を検索
                firstSlashLocation = vertexData.find("/");

                if (firstSlashLocation == std::string::npos)
                {
                    // 座標を頂点に設定
                    positionIndex = std::stoi(vertexData) - INDEX_CORRECTION;
                    tempVertex.position_ = rPositions[positionIndex];
                }
                else
                {
                    // 座標を頂点に設定
                    positionIndex = std::stoi(vertexData.substr(0, firstSlashLocation)) - INDEX_CORRECTION;
                    tempVertex.position_ = rPositions[positionIndex];

                    // 2つ目の'/'の位置を検索
                    secondSlashLocation = vertexData.find("/", firstSlashLocation + 1);

                    if (secondSlashLocation > firstSlashLocation + 1)
                    {
                        // テクスチャ座標を頂点に設定
                        textureCoordIndex = std::stoi(vertexData.substr(firstSlashLocation + 1, secondSlashLocation)) - INDEX_CORRECTION;
                        tempVertex.textureCoord_ = rTextureCoords[textureCoordIndex];
                    }
                }

                // 法線ベクトルを頂点に設定
                normalIndex = std::stoi(vertexData.substr(secondSlashLocation + 1, vertexData.length())) - INDEX_CORRECTION;
                tempVertex.normal_ = rNormals[normalIndex];

                // ポリゴンの頂点数を1増やす
                ++polygonVertexCount;

                // 頂点を追加
                (*pVertices).push_back(tempVertex);

            } while ((*pStringStream).good());

            assert(polygonVertexCount >= 3);

            // 三角形ポリゴンに分割しつつ、インデックスを格納
            for (int32_t i = 0; i < polygonVertexCount - 2; ++i)
            {
                (*pIndices).push_back(vertexCount_ + 0);
                (*pIndices).push_back(vertexCount_ + i + 1);
                (*pIndices).push_back(vertexCount_ + i + 2);

                // ポリゴン数を1増やす
                ++polygonCount_;
            }

            // ポリゴンの頂点数を加算
            vertexCount_ += polygonVertexCount;
        }


        /*************************************************************//**
         *
         *  @brief  色を設定する
         *  @param  文字列ストリーム
         *  @param  色
         *  @return なし
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::SetColor(std::stringstream* pStringStream, Vector3* pColor)
        {
            (*pStringStream) >> pColor->x_ >> pColor->y_ >> pColor->z_;
        }
    }
}