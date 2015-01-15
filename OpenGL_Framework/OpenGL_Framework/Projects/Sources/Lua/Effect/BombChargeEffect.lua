--[[ �o�C���h���Ă���֐�����уN���X ]]--[[


1. S_ParticleData

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

�E void Entry(const S_ParticleData& rData);


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
�E void ResetCount();


6. C_RandomManager

�E float Random(float min = 0.0f, float max = 1.0f);


]]


--[[ �~���������擾���� --]]

-- double raduis
-- C_RandomManager randomManager

 function CircumferenceRandom(radius, randomManager)

	-- 2��
	local PI2 = 6.283185

	-- �p�x�����߂�
	local angle = randomManager:Random(0.0, PI2)

	-- �e������ݒ�
	local x = math.cos(angle) * radius
	local y = math.sin(angle) * radius

	return x, y

 end


--[[ �{���̃`���[�W�G�t�F�N�g�̃��W�b�N���������� --]]

--[[ ������ ]]

-- IC_ParticleSystem& rCircleParticleSystem
-- IC_ParticleSystem& rRingParticleSystem
-- C_FrameCounter& rFrameCounter
-- C_RandomManager& rRandomManager
-- S_Vector3 rPosition

function BombChargeEffectLogic(rCircleParticleSystem, rRingParticleSystem, rFrameCounter, rRandomManager, rPosition)

	-- �p�[�e�B�N���̏��
	local particleData = S_ParticleData()

	-- ���݂̃t���[����
	local nowFrame = rFrameCounter:GetCount()

	if  nowFrame % 15 == 1 and nowFrame < 40 then

		particleData.lifeFrame_ = 20
		particleData.position_ = rPosition
		particleData.velocity_ = S_Vector3()
		particleData.startAcceleration_ = S_Vector3()
		particleData.endAcceleration_ = S_Vector3()
		particleData.startAngle_ = 0.0
		particleData.endAngle_ = 0.0
		particleData.startWidth_ = 20.0
		particleData.endWidth__ = 0.001
		particleData.startHeight_ = 20.0
		particleData.endHeight_ = 0.001
		particleData.startColor_ = S_Vector4(1.0, 1.0, 0.8, 1.0)
		particleData.endColor_ = S_Vector4(1.0, 1.0, 1.0, 0.3)

		rRingParticleSystem:Entry(particleData)

		particleData.lifeFrame_ = 20
		particleData.position_ = rPosition
		particleData.velocity_ = S_Vector3()
		particleData.startAcceleration_ = S_Vector3()
		particleData.endAcceleration_ = S_Vector3()
		particleData.startAngle_ = 0.0
		particleData.endAngle_ = 0.0
		particleData.startWidth_ = 15.0
		particleData.endWidth__ = 0.001
		particleData.startHeight_ = 15.0
		particleData.endHeight_ = 0.001
		particleData.startColor_ = S_Vector4(1.0, 1.0, 1.0, 0.2)
		particleData.endColor_ = S_Vector4(0.7, 0.7, 0.2, 0.5)

		rCircleParticleSystem:Entry(particleData)

	end

	if  nowFrame >= 1 and nowFrame < 30 then

		local x, y = CircumferenceRandom(15.0, rRandomManager)
		local green = rRandomManager:Random(0.0, 0.5)

		particleData.lifeFrame_ = 25
		particleData.position_ = rPosition + S_Vector3(x, y, 1.0)
		particleData.velocity_ = S_Vector3(-x/ particleData.lifeFrame_, -y / particleData.lifeFrame_, 0.0)
		particleData.startAcceleration_ = S_Vector3()
		particleData.endAcceleration_ = S_Vector3()
		particleData.startAngle_ = 0.0
		particleData.endAngle_ = 0.0
		particleData.startWidth_ = 2.5
		particleData.endWidth__ = 0.001
		particleData.startHeight_ = 2.5
		particleData.endHeight_ = 0.001
		particleData.startColor_ = S_Vector4(1.0, green, 0.0, 1.0)
		particleData.endColor_ = S_Vector4(0.7, green, 0.2, 0.5)

		rCircleParticleSystem:Entry(particleData)

		x, y = CircumferenceRandom(15.0, rRandomManager)

		particleData.lifeFrame_ = 20
		particleData.position_ = rPosition + S_Vector3(x, y, 1.0)
		particleData.velocity_ = S_Vector3(-x/ particleData.lifeFrame_, -y / particleData.lifeFrame_, 0.0)
		particleData.startAcceleration_ = S_Vector3()
		particleData.endAcceleration_ = S_Vector3()
		particleData.startAngle_ = 0.0
		particleData.endAngle_ = 0.0
		particleData.startWidth_ = 3.0
		particleData.endWidth__ = 0.1
		particleData.startHeight_ = 3.0
		particleData.endHeight_ = 0.1
		particleData.startColor_ = S_Vector4(1.0, 0.6, 0.2, 0.0)
		particleData.endColor_ = S_Vector4(1.0, 0.8, 0.0, 0.5)

		rCircleParticleSystem:Entry(particleData)

	end

	if  nowFrame == 45 then

		return false

	end

	return true

end
