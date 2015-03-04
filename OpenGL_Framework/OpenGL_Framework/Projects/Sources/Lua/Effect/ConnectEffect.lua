--[[ バインドしてある関数およびクラス ]]--[[


1. S_CreateParticleData

・ int32_t lifeFrame_ = 0;
・ Vector3 position_;
・ Vector3 velocity_;
・ Vector3 startAcceleration_
・ Vector3 endAcceleration_;
・ float startAngle_ = 0.0f;
・ float endAngle_ = 0.0f;
・ float startWidth_ = 0.0f;
・ float endWidth_ = 0.0f;
・ float startHeight_ = 0.0f;
・ float endHeight_ = 0.0f;
・ Vector4 startColor_;
・ Vector4 endColor_;


2. IC_ParticleSystem

・ void Entry(const S_ParticleCreateData& rData);


3. S_Vector3

・ S_Vector3();
・ S_Vector3(float value);
・ S_Vector3(float x, float y, float z);


4. S_Vector4

・ S_Vector4();
・ S_Vector4(float value);
・ S_Vector4(float x, float y, float z, float w);


5. C_FrameCounter

・ int32_t GetCount();
・ void SetCount(int32_t count);
・ void ResetCount();


6. C_RandomGenerator

・ float Random(float min = 0.0f, float max = 1.0f);


]]


--[[ 円周乱数を取得する --]]

-- double raduis
-- C_RandomGenerator randomGenerator

 function CircumferenceRandom(radius, randomGenerator)

	-- 2π
	local PI2 = 6.283185

	-- 角度を求める
	local angle = randomGenerator:Random(0.0, PI2)

	-- 各成分を設定
	local x = math.cos(angle) * radius
	local y = math.sin(angle) * radius

	return x, y

 end


--[[ 引き数 ]]

-- IC_ParticleSystem& rCircleParticleSystem
-- IC_ParticleSystem& rRingParticleSystem
-- C_FrameCounter& rFrameCounter
-- C_RandomGenerator& rRandomGenerator
-- S_Vector3 rPosition

function ConnectEffectLogic(rCircleParticleSystem, rRingParticleSystem, rFrameCounter, rRandomGenerator, rPosition)

	-- パーティクルの情報
	local particleCreateData = S_ParticleCreateData()

	-- 現在のフレーム数
	local nowFrame = rFrameCounter:GetCount()

	local angle = 0.0
	local piDiv2 = 1.570796
	local velocityX = 0.23
	local velocityY = 0.23

	for i = 1, 4 do

		if i % 2 == 1 then

			for j = 1, 2 do

				particleCreateData.lifeFrame_ = 23
				particleCreateData.position_ = rPosition + S_Vector3(0.0, velocityY * 2.0, 1.5)
				particleCreateData.velocity_ = S_Vector3(0.0, velocityY, 0.0)
				particleCreateData.startAcceleration_ = S_Vector3()
				particleCreateData.endAcceleration_ = S_Vector3()
				particleCreateData.startAngle_ = angle
				particleCreateData.endAngle_ = angle
				particleCreateData.startWidth_ = 0.1
				particleCreateData.endWidth_ = 0.2
				particleCreateData.startHeight_ = 0.1
				particleCreateData.endHeight_ = 4.0
				particleCreateData.startColor_ = S_Vector4(0.2, 0.9, 0.1, 1.0)
				particleCreateData.endColor_ = S_Vector4(0.2, 0.9, 0.1, 0.3)

				rCircleParticleSystem:Entry(particleCreateData)

			end

			velocityY = -velocityY;

		else

			for j = 1, 2 do

				particleCreateData.lifeFrame_ = 23
				particleCreateData.position_ = rPosition + S_Vector3(velocityX * 2.0, 0.0, 1.5)
				particleCreateData.velocity_ = S_Vector3(velocityX, 0.0, 0.0)
				particleCreateData.startAcceleration_ = S_Vector3()
				particleCreateData.endAcceleration_ = S_Vector3()
				particleCreateData.startAngle_ = angle
				particleCreateData.endAngle_ = angle
				particleCreateData.startWidth_ = 0.1
				particleCreateData.endWidth_ = 0.2
				particleCreateData.startHeight_ = 0.1
				particleCreateData.endHeight_ = 4.0
				particleCreateData.startColor_ = S_Vector4(0.2, 0.9, 0.1, 1.0)
				particleCreateData.endColor_ = S_Vector4(0.2, 0.9, 0.1, 0.3)

				rCircleParticleSystem:Entry(particleCreateData)

			end

			velocityX = -velocityX

		end


		angle = angle + piDiv2

	end

	particleCreateData.lifeFrame_ = 20
	particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 1.5)
	particleCreateData.velocity_ = S_Vector3()
	particleCreateData.startAcceleration_ = S_Vector3()
	particleCreateData.endAcceleration_ = S_Vector3()
	particleCreateData.startAngle_ = 0.0
	particleCreateData.endAngle_ = 0.0
	particleCreateData.startWidth_ = 0.1
	particleCreateData.endWidth_ = 8.5
	particleCreateData.startHeight_ = 0.1
	particleCreateData.endHeight_ =8.5
	particleCreateData.startColor_ = S_Vector4(1.0, 1.0, 1.0, 1.0)
	particleCreateData.endColor_ = S_Vector4(1.0, 1.0, 1.0, 0.7)

	rRingParticleSystem:Entry(particleCreateData)

	particleCreateData.lifeFrame_ = 20
	particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 1.5)
	particleCreateData.velocity_ = S_Vector3()
	particleCreateData.startAcceleration_ = S_Vector3()
	particleCreateData.endAcceleration_ = S_Vector3()
	particleCreateData.startAngle_ = 0.0
	particleCreateData.endAngle_ = 0.0
	particleCreateData.startWidth_ = 0.1
	particleCreateData.endWidth_ = 4.5
	particleCreateData.startHeight_ = 0.1
	particleCreateData.endHeight_ =4.5
	particleCreateData.startColor_ = S_Vector4(1.0, 1.0, 1.0, 0.8)
	particleCreateData.endColor_ = S_Vector4(1.0, 1.0, 1.0, 0.1)

	rCircleParticleSystem:Entry(particleCreateData)

	particleCreateData.lifeFrame_ = 25
	particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 1.5)
	particleCreateData.velocity_ = S_Vector3()
	particleCreateData.startAcceleration_ = S_Vector3()
	particleCreateData.endAcceleration_ = S_Vector3()
	particleCreateData.startAngle_ = 0.0
	particleCreateData.endAngle_ = 0.0
	particleCreateData.startWidth_ = 0.1
	particleCreateData.endWidth_ = 15.5
	particleCreateData.startHeight_ = 0.1
	particleCreateData.endHeight_ =15.5
	particleCreateData.startColor_ = S_Vector4(0.8, 0.6, 0.1, 0.8)
	particleCreateData.endColor_ = S_Vector4(0.8, 0.6, 0.1, 0.1)

	rCircleParticleSystem:Entry(particleCreateData)

	return false

end
