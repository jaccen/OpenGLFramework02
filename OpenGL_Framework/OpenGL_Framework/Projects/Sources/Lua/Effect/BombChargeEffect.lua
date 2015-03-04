--[[ �o�C���h���Ă���֐�����уN���X ]]--[[


1. S_CreateParticleData

�E int32_t lifeFrame_ = 0;
�E Vector3 position_;
�E Vector3 velocity_;
�E Vector3 startAcceleration_
�E Vector3 endAcceleration_;
�E float startAngle_ = 0.0f;
�E float endAngle_ = 0.0f;
�E float startWidth_ = 0.0f;
�E float endWidth_ = 0.0f;
�E float startHeight_ = 0.0f;
�E float endHeight_ = 0.0f;
�E Vector4 startColor_;
�E Vector4 endColor_;


2. IC_ParticleSystem

�E void Entry(const S_ParticleCreateData& rData);


3. S_Vector3

�E S_Vector3();
�E S_Vector3(float value);
�E S_Vector3(float x, float y, float z);


4. S_Vector4

�E S_Vector4();
�E S_Vector4(float value);
�E S_Vector4(float x, float y, float z, float w);


5. C_FrameCounter

�E int32_t GetCount();
�E void SetCount(int32_t count);
�E void ResetCount();


6. C_RandomGenerator

�E float Random(float min = 0.0f, float max = 1.0f);


]]


--[[ �~���������擾���� --]]

-- double raduis
-- C_RandomGenerator randomGenerator

 function CircumferenceRandom(radius, randomGenerator)

	-- 2��
	local PI2 = 6.283185

	-- �p�x�����߂�
	local angle = randomGenerator:Random(0.0, PI2)

	-- �e������ݒ�
	local x = math.cos(angle) * radius
	local y = math.sin(angle) * radius

	return x, y

 end


--[[ ������ ]]

-- IC_ParticleSystem& rCircleParticleSystem
-- IC_ParticleSystem& rRingParticleSystem
-- C_FrameCounter& rFrameCounter
-- C_RandomGenerator& rRandomGenerator
-- S_Vector3 rPosition

function BombChargeEffectLogic(rCircleParticleSystem, rRingParticleSystem, rFrameCounter, rRandomGenerator, rPosition)

	-- �p�[�e�B�N���̏��
	local particleCreateData = S_ParticleCreateData()

	-- ���݂̃t���[����
	local nowFrame = rFrameCounter:GetCount()

	if  nowFrame < 30 then

		particleCreateData.lifeFrame_ = 30
		particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 1.5)
		particleCreateData.velocity_ = S_Vector3()
		particleCreateData.startAcceleration_ = S_Vector3()
		particleCreateData.endAcceleration_ = S_Vector3()
		particleCreateData.startAngle_ = 0.0
		particleCreateData.endAngle_ = 0.0
		particleCreateData.startWidth_ = 28.0
		particleCreateData.endWidth_ = 0.5
		particleCreateData.startHeight_ = 28.0
		particleCreateData.endHeight_ = 0.5
		particleCreateData.startColor_ = S_Vector4(1.0, 0.8, 0.5, 0.01)
		particleCreateData.endColor_ = S_Vector4(0.9, 0.6, 0.8, 0.11)

		rCircleParticleSystem:Entry(particleCreateData)


	end

	if  nowFrame >= 1 and nowFrame < 30 then


		for i = 1, 3 do

			local x, y = CircumferenceRandom(15.0, rRandomGenerator)
			local green = rRandomGenerator:Random(0.5, 0.9)
			local width = rRandomGenerator:Random(5.5, 15.5)
			local angle = math.atan2(y,x)

			particleCreateData.lifeFrame_ = 20
			particleCreateData.position_ = rPosition + S_Vector3(x, y, 5.0)
			particleCreateData.velocity_ = S_Vector3(-x/ particleCreateData.lifeFrame_, -y / particleCreateData.lifeFrame_, 0.0)
			particleCreateData.startAcceleration_ = S_Vector3()
			particleCreateData.endAcceleration_ = S_Vector3()
			particleCreateData.startAngle_ = angle
			particleCreateData.endAngle_ = angle
			particleCreateData.startWidth_ = width
			particleCreateData.endWidth_ = 0.5
			particleCreateData.startHeight_ = 0.5
			particleCreateData.endHeight_ = 0.001
			particleCreateData.startColor_ = S_Vector4(1.0, green, 0.7, 0.8)
			particleCreateData.endColor_ = S_Vector4(0.3, green, 0.7, 0.4)

			rCircleParticleSystem:Entry(particleCreateData)

		end

	end

	if  nowFrame == 45 then

		return false

	end

	return true

end
