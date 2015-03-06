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

function OptionSmallBeamCollisionEffectLogic(rCircleParticleSystem, rRingParticleSystem, rFrameCounter, rRandomGenerator, rPosition)

	-- パーティクルの情報
	local particleCreateData = S_ParticleCreateData()

	-- 現在のフレーム数
	local nowFrame = rFrameCounter:GetCount()

	local PI2 = 6.283185

	local velocityX, velocityY, velocityFactor = 0.0, 0.0, 0.0
	local angle = 0.0
	local red = 0.0

	for i = 1, 5 do

		angle = rRandomGenerator:Random(0.0, PI2)

		velocityX = math.cos(angle) * 0.15
		velocityY= math.sin(angle) * 0.15

		particleCreateData.lifeFrame_ = 10
		particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 5.0)
		particleCreateData.velocity_ = S_Vector3(0.0, 0.0, 0.0)
		particleCreateData.startAcceleration_ = S_Vector3()
		particleCreateData.endAcceleration_ = S_Vector3()
		particleCreateData.startAngle_ = angle
		particleCreateData.endAngle_ = angle
		particleCreateData.startWidth_ = 0.7
		particleCreateData.endWidth_ = rRandomGenerator:Random(1.2, 2.3)
		particleCreateData.startHeight_ = 0.12
		particleCreateData.endHeight_ = 0.1
		particleCreateData.startColor_ = S_Vector4(1.0, 0.8, 0.9, 0.1)
		particleCreateData.endColor_ = S_Vector4(0.5, 0.7, 1.0, 0.4)

		rCircleParticleSystem:Entry(particleCreateData)

		particleCreateData.lifeFrame_ = 10
		particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 5.0)
		particleCreateData.velocity_ = S_Vector3(0.0, 0.0, 0.0)
		particleCreateData.startAcceleration_ = S_Vector3()
		particleCreateData.endAcceleration_ = S_Vector3()
		particleCreateData.startAngle_ = angle
		particleCreateData.endAngle_ = angle
		particleCreateData.startWidth_ = 0.1
		particleCreateData.endWidth_ = particleCreateData.endWidth_ - 0.8
		particleCreateData.startHeight_ = 0.11
		particleCreateData.endHeight_ = 0.1
		particleCreateData.startColor_ = S_Vector4(0.3, 0.6, 1.0, 0.3)
		particleCreateData.endColor_ = S_Vector4(0.4, 0.7, 1.0, 0.7)

		rCircleParticleSystem:Entry(particleCreateData)

	end

	particleCreateData.lifeFrame_ = 10
	particleCreateData.position_ = rPosition + S_Vector3(0.0, 0.0, 5.0)
	particleCreateData.velocity_ = S_Vector3(0.0, 0.0, 0.0)
	particleCreateData.startAcceleration_ = S_Vector3()
	particleCreateData.endAcceleration_ = S_Vector3()
	particleCreateData.startAngle_ = angle
	particleCreateData.endAngle_ = angle
	particleCreateData.startWidth_ = 0.3
	particleCreateData.endWidth_ = 2.5
	particleCreateData.startHeight_ = 0.3
	particleCreateData.endHeight_ = 2.5
	particleCreateData.startColor_ = S_Vector4(0.7, 0.5, 1.0, 0.3)
	particleCreateData.endColor_ = S_Vector4(0.7, 0.0, 1.0, 0.05)

	rCircleParticleSystem:Entry(particleCreateData)

	return false

end
