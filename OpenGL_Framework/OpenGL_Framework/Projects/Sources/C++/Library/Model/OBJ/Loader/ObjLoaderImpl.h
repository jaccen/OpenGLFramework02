/* �w�b�_�t�@�C�� */
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
//! @brief ���f��
//! @brief ���f���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief OBJ
    //! @brief OBJ�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace OBJ
    {
        //-------------------------------------------------------------
        //!
        //! @brief OBJ���[�_�[�C���v�������g
        //! @brief OBJ���[�_�[�̃v���C�x�[�g���̎���
        //!
        //-------------------------------------------------------------
        class C_ObjLoader::C_ObjLoaderImpl
        {
        public:
            C_ObjLoaderImpl();                                                                                  // �R���X�g���N�^
            ~C_ObjLoaderImpl();                                                                                 // �f�X�g���N�^
            void Load(const std::string& rFilePath);                                                            // ���[�h����
            void Release();                                                                                     // �������
            const S_Mesh& GetMesh() const;                                                                      // ���b�V�����擾
            uint32_t GetMaterialCount() const;                                                                  // �}�e���A�������擾
            int32_t GetMaterialIndex(const std::string& rName) const;                                           // �}�e���A����ID���擾
            const S_Material& GetMaterial(int32_t id) const;                                                    // �}�e���A�����擾
        private:
            S_Mesh mesh_;                                                                                       ///< @brief ���b�V��
            std::deque<S_Material> materials_;                                                                  ///< @brief �}�e���A��
            std::unordered_map<std::string, int16_t> materialIdDictionary_;                                     ///< @brief �}�e���A��ID�̎���
            int32_t polygonCount_ = 0;                                                                          ///< @brief �|���S���̐�
            int32_t vertexCount_ = 0;                                                                           ///< @brief ���_��

            void ParseObjFile(const std::string& rFilePath);                                                    // OBJ�t�@�C���̉��
            void ParseMtlFile(const std::string& rFilePath);                                                    // MTL�t�@�C���̉��
            void AddPosition(std::stringstream* pStringStream, std::vector<Vector3>* pPositions);               // ���_���W��ǉ�
            void AddNormal(std::stringstream* pStringStream, std::vector<Vector3>* pNormals);                   // �@���x�N�g����ǉ�
            void AddTextureCoord(std::stringstream* pStringStream, std::vector<Vector2>* pTextureCoords);       // �e�N�X�`�����W��ǉ�
            void AddVertex(std::stringstream* pStringStream,                                                    // ���_��ǉ�     
                           const std::vector<Vector3>& rPositions,
                           const std::vector<Vector3>& rNormals,
                           const std::vector<Vector2>& rTextureCoords,
                           std::vector<S_Vertex>* pVertices,
                           std::vector<uint16_t>* pIndices);
            void SetColor(std::stringstream* pStringStream, Vector3* pColor);                                   // �F��ݒ�
        };


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ObjLoader::C_ObjLoaderImpl::C_ObjLoaderImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ObjLoader::C_ObjLoaderImpl::~C_ObjLoaderImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ���[�h�������s��
         *  @param  �t�@�C���p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::Load(const std::string& rFilePath)
        {
            // OBJ�t�@�C�������
            ParseObjFile(rFilePath);
        }


        /*************************************************************//**
         *
         *  @brief  ����������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
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
         *  @brief  ���b�V�����擾����
         *  @param  �Ȃ�
         *  @return ���b�V��
         *
         ****************************************************************/
        const S_Mesh& C_ObjLoader::C_ObjLoaderImpl::GetMesh() const
        {
            return mesh_;
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A�������擾����
         *  @param  �Ȃ�
         *  @return �}�e���A����
         *
         ****************************************************************/
        uint32_t C_ObjLoader::C_ObjLoaderImpl::GetMaterialCount() const
        {
            return materials_.size();
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A���C���f�b�N�X���擾����
         *  @param  �}�e���A����
         *  @return �}�e���A���C���f�b�N�X
         *
         ****************************************************************/
        int32_t C_ObjLoader::C_ObjLoaderImpl::GetMaterialIndex(const std::string& rName) const
        {
            return materialIdDictionary_.at(rName);
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A�����擾����
         *  @param  �}�e���A���C���f�b�N�X
         *  @return �}�e���A��
         *
         ****************************************************************/
        const S_Material& C_ObjLoader::C_ObjLoaderImpl::GetMaterial(int32_t index) const
        {
            return materials_.at(index);
        }


        /*************************************************************//**
         *
         *  @brief  OBJ�t�@�C���̉�͂��s��
         *  @param  �t�@�C���p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::ParseObjFile(const std::string& rFilePath)
        {
            // �t�@�C�����J��
            std::ifstream inFile(rFilePath, std::ifstream::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ObjLoaderImpl::LoadObjFile ] : OBJ�t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // ���W�E�@���x�N�g���E�e�N�X�`�����W
            std::vector<Vector3> positions;
            std::vector<Vector3> normals;
            std::vector<Vector2> textureCoords;
            std::vector<S_Vertex> vertices;
            std::vector<uint16_t> indices;

            // �e���������m��
            const int32_t RESERVE_NUMBER = 100000;

            mesh_.vertices_.reserve(RESERVE_NUMBER);
            positions.reserve(RESERVE_NUMBER);
            normals.reserve(RESERVE_NUMBER);
            textureCoords.reserve(RESERVE_NUMBER);

            // 1�s���̃f�[�^���擾���A������X�g���[���Ɋi�[
            std::string lineData;
            std::getline(inFile, lineData);
            lineData = Common::C_CommonHelper::s_TrimString(lineData);
            std::stringstream stringStream(lineData);

            // ���ʗp����
            std::string distinctionCharacter;

            // �t�@�C���̍Ō�̍s������܂Ń��[�v
            while (inFile.eof() == false)
            {
                // �����񂪑��݂��A���ꂪ�R�����g�łȂ��ꍇ�͊e�f�[�^��ݒ�
                if (lineData.length() > 0 && lineData.at(0) != '#')
                {
                    // ������X�g���[�����画�ʗp�̕������擾
                    stringStream >> distinctionCharacter;

                    /* ���W */
                    if (distinctionCharacter == "v")
                    {
                        AddPosition(&stringStream, &positions);
                    }
                    /* �e�N�X�`�����W */
                    else if (distinctionCharacter == "vt")
                    {
                        AddTextureCoord(&stringStream, &textureCoords);
                    }
                    /* �@���x�N�g�� */
                    else if (distinctionCharacter == "vn")
                    {
                        AddNormal(&stringStream, &normals);
                    }
                    /* �|���S��( �� ) */
                    else if (distinctionCharacter == "f")
                    {
                        AddVertex(&stringStream,
                                  positions,
                                  normals,
                                  textureCoords,
                                  &vertices,
                                  &indices);
                    }
                    /* �}�e���A���t�@�C�� */
                    else if (distinctionCharacter == "mtllib")
                    {
                        // �}�e���A���t�@�C�������擾
                        std::string materialFileName;
                        stringStream >> materialFileName;
                        materialFileName = Path::C_PathAnalizer::s_GetFileName(materialFileName);

                        // �f�B���N�g�������擾���A�}�e���A���t�@�C�����ƘA��
                        std::string directoryName = Path::C_PathAnalizer::s_GetDirectoryName(rFilePath);
                        std::string materialFilePath = directoryName + materialFileName;

                        // MTL�t�@�C�������
                        ParseMtlFile(materialFileName);
                    }

                }

                // ������X�g���[���̃o�b�t�@���N���A
                stringStream.str("");
                stringStream.clear(std::stringstream::goodbit);

                // 1�s���̃f�[�^��ǂݍ��݁A������X�g���[���Ɋi�[
                std::getline(inFile, lineData);
                lineData = Common::C_CommonHelper::s_TrimString(lineData);
                stringStream << lineData;
            }

            // ���b�V���̒��_���C���f�b�N�X���擾
            auto& rMeshVertices = mesh_.vertices_;
            rMeshVertices.reserve(vertices.size());

            size_t indicesCount = indices.size();
            auto& rMeshIndices = mesh_.indices_;
            rMeshIndices.reserve(indicesCount);

            for (size_t i = 0; i < indicesCount; ++i)
            {
                auto& rVertex = vertices[indices[i]];

                // �d�����Ă��钸�_���������A�������ʂɂ�蒸�_�ƃC���f�b�N�X������U��
                auto iterator = std::find(rMeshVertices.begin(), rMeshVertices.end(), rVertex);

                /* �d�����Ă��Ȃ� */
                if (iterator == rMeshVertices.end())
                {
                    rMeshIndices.push_back(rMeshVertices.size());
                    rMeshVertices.push_back(rVertex);
                }
                /* �d�����Ă��� */
                else
                {
                    size_t index = std::distance(rMeshVertices.begin(), iterator);
                    rMeshIndices.push_back(index);
                }
            }

            // ���_�̗]���ȃ������̈���Ȃ���
            rMeshVertices.shrink_to_fit();
        }


        /*************************************************************//**
         *
         *  @brief  MTL�t�@�C���̉�͂��s��
         *  @param  �t�@�C���p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::ParseMtlFile(const std::string& rFilePath)
        {
            // �t�@�C�����J��
            std::ifstream inFile(rFilePath);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ObjLoaderImpl::ParseMtlFile ] : MTL�t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // ��s���̃f�[�^���擾���A������X�g���[���Ɋi�[
            std::string lineData;
            std::getline(inFile, lineData);
            lineData = Common::C_CommonHelper::s_TrimString(lineData);
            std::stringstream stringStream(lineData);

            // ���ʗp����
            std::string distinctionCharacter;

            // �}�e���A���̃C���f�b�N�X
            int materialIndex = -1;

            // �t�@�C���̍Ō�̍s������܂Ń��[�v
            while (inFile.eof() == false)
            {
                // �����񂪑��݂��A���ꂪ�R�����g�łȂ��ꍇ�͊e�f�[�^��ݒ�
                if (lineData.length() > 0 && lineData.at(0) != '#')
                {
                    // ������X�g���[�����画�ʗp�̕������擾
                    stringStream >> distinctionCharacter;

                    /* �V�����}�e���A�� */
                    if (distinctionCharacter == "newmtl")
                    {
                        // �}�e���A���̃C���f�b�N�X1����
                        ++materialIndex;

                        // �}�e���A����1�ǉ����A�}�e���A�������擾
                        materials_.emplace_back();
                        stringStream >> materials_[materialIndex].name_;

                        // �}�e���A�����������ɓo�^
                        materialIdDictionary_.emplace(materials_[materialIndex].name_, materialIndex);

                        // ��ԍŏ��̃}�e���A�������b�V���̃}�e���A���Ƃ��Ė��O��ݒ�
                        if (mesh_.materialName_.empty() == true) mesh_.materialName_ = materials_[materialIndex].name_;
                    }
                    /* �A���r�G���g�J���[ */
                    else if (distinctionCharacter == "Ka")
                    {
                        SetColor(&stringStream, &materials_[materialIndex].ambient_);
                    }
                    /* �f�B�t���[�Y�J���[ */
                    else if (distinctionCharacter == "Kd")
                    {
                        SetColor(&stringStream, &materials_[materialIndex].diffuse_);
                    }
                    /* �X�y�L�����[�J���[ */
                    else if (distinctionCharacter == "Ks")
                    {
                        SetColor(&stringStream, &materials_[materialIndex].specular_);
                    }
                    /* �s�����x */
                    else if (distinctionCharacter == "d" || distinctionCharacter == "Tr")
                    {
                        stringStream >> materials_[materialIndex].opacity_;
                    }
                    /* ���� */
                    else if (distinctionCharacter == "Ns")
                    {
                        stringStream >> materials_[materialIndex].shininess_;
                    }
                    /* �A���r�G���g�}�b�v */
                    else if (distinctionCharacter == "map_Ka")
                    {
                        stringStream >> materials_[materialIndex].ambientTextureFileName_;
                    }
                    /* �f�B�t���[�Y�}�b�v */
                    else if (distinctionCharacter == "map_Kd")
                    {
                        stringStream >> materials_[materialIndex].diffuseTextureFileName_;
                    }
                    /* �X�y�L�����[�}�b�v */
                    else if (distinctionCharacter == "map_Ks")
                    {
                        stringStream >> materials_[materialIndex].specularTextureFileName_;
                    }
                }

                // ������X�g���[���̃o�b�t�@���N���A
                stringStream.str("");
                stringStream.clear(std::stringstream::goodbit);

                // 1�s���̃f�[�^��ǂݍ��݁A������X�g���[���Ɋi�[
                std::getline(inFile, lineData);
                lineData = Common::C_CommonHelper::s_TrimString(lineData);
                stringStream << lineData;
            }
        }


        /*************************************************************//**
         *
         *  @brief  ���W��ǉ�����
         *  @param  ������X�g���[��
         *  @param  ���W
         *  @return �Ȃ�
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
         *  @brief  �@���x�N�g����ǉ�����
         *  @param  ������X�g���[��
         *  @param  �@���x�N�g��
         *  @return �Ȃ�
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
         *  @brief  �e�N�X�`�����W��ǉ�����
         *  @param  ������X�g���[��
         *  @param  �e�N�X�`�����W
         *  @return �Ȃ�
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
         *  @brief  ���_��ǉ�����
         *  @param  ������X�g���[��
         *  @param  ���W
         *  @param  �@���x�N�g��
         *  @param  �e�N�X�`�����W
         *  @param  ���_
         *  @param  �C���f�b�N�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::AddVertex(std::stringstream* pStringStream,
                                                     const std::vector<Vector3>& rPositions,
                                                     const std::vector<Vector3>& rNormals,
                                                     const std::vector<Vector2>& rTextureCoords,
                                                     std::vector<S_Vertex>* pVertices,
                                                     std::vector<uint16_t>* pIndices)
        {
            // �|���S���̒��_��
            int32_t polygonVertexCount = 0;

            // ���̒��_
            S_Vertex tempVertex;

            // ���_�f�[�^
            std::string vertexData;

            // '/'�̓����Ă���ʒu���i�[����ϐ�
            size_t firstSlashLocation = 0, secondSlashLocation = 0;

            // �e�C���f�b�N�X
            int32_t positionIndex = 0, textureCoordIndex = 0, normalIndex = 0;

            // �C���f�b�N�X�̕␳�l
            const int32_t INDEX_CORRECTION = 1;

            do
            {
                // ���_�f�[�^���擾
                (*pStringStream) >> vertexData;

                // 1�ڂ�'/'�̈ʒu������
                firstSlashLocation = vertexData.find("/");

                if (firstSlashLocation == std::string::npos)
                {
                    // ���W�𒸓_�ɐݒ�
                    positionIndex = std::stoi(vertexData) - INDEX_CORRECTION;
                    tempVertex.position_ = rPositions[positionIndex];
                }
                else
                {
                    // ���W�𒸓_�ɐݒ�
                    positionIndex = std::stoi(vertexData.substr(0, firstSlashLocation)) - INDEX_CORRECTION;
                    tempVertex.position_ = rPositions[positionIndex];

                    // 2�ڂ�'/'�̈ʒu������
                    secondSlashLocation = vertexData.find("/", firstSlashLocation + 1);

                    if (secondSlashLocation > firstSlashLocation + 1)
                    {
                        // �e�N�X�`�����W�𒸓_�ɐݒ�
                        textureCoordIndex = std::stoi(vertexData.substr(firstSlashLocation + 1, secondSlashLocation)) - INDEX_CORRECTION;
                        tempVertex.textureCoord_ = rTextureCoords[textureCoordIndex];
                    }
                }

                // �@���x�N�g���𒸓_�ɐݒ�
                normalIndex = std::stoi(vertexData.substr(secondSlashLocation + 1, vertexData.length())) - INDEX_CORRECTION;
                tempVertex.normal_ = rNormals[normalIndex];

                // �|���S���̒��_����1���₷
                ++polygonVertexCount;

                // ���_��ǉ�
                (*pVertices).push_back(tempVertex);

            } while ((*pStringStream).good());

            assert(polygonVertexCount >= 3);

            // �O�p�`�|���S���ɕ������A�C���f�b�N�X���i�[
            for (int32_t i = 0; i < polygonVertexCount - 2; ++i)
            {
                (*pIndices).push_back(vertexCount_ + 0);
                (*pIndices).push_back(vertexCount_ + i + 1);
                (*pIndices).push_back(vertexCount_ + i + 2);

                // �|���S������1���₷
                ++polygonCount_;
            }

            // �|���S���̒��_�������Z
            vertexCount_ += polygonVertexCount;
        }


        /*************************************************************//**
         *
         *  @brief  �F��ݒ肷��
         *  @param  ������X�g���[��
         *  @param  �F
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ObjLoader::C_ObjLoaderImpl::SetColor(std::stringstream* pStringStream, Vector3* pColor)
        {
            (*pStringStream) >> pColor->x_ >> pColor->y_ >> pColor->z_;
        }
    }
}