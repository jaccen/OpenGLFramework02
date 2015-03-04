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

function PlayerExplosionEffectLogic(rCircleParticleSystem, rSmokeParticleSystem, rFrameCounter, rRandomGenerator, rPosition)

	-- パーティクルの情報
	local particleCreateData = S_ParticleCreateData()
	local angle =  rRandomGenerator:Random(-3.14, 3.14)


	-- 現在のフレーム数
	local nowFrame = rFrameCounter:GetCount()

	particleCreateData.lifeFrame_ = 50
	particleCreateData.position_ = rPosition
	particleCreateData.velocity_ = S_Vector3()
	particleCreateData.startAcceleration_ = S_Vector3()
	particleCreateData.endAcceleration_ = S_Vector3()
	particleCreateData.startAngle_ = 0.0
	particleCreateData.endAngle_ = angle
	particleCreateData.startWidth_ = 0.5
	particleCreateData.endWidth_ = 17.0
	particleCreateData.startHeight_ = 0.5
	particleCreateData.endHeight_ = 17.0
	particleCreateData.startColor_ = S_Vector4(0.3, 0.4, 1.0, 0.6)
	particleCreateData.endColor_ = S_Vector4(0.2, 0.4, 1.0, 0.1)

	rSmokeParticleSystem:Entry(particleCreateData)


    local addPositionX = rRandomGenerator:Random(-0.7, 0.7)
	local addPositionY = rRandomGenerator:Random(-0.7, 0.7)

	angle =  rRandomGenerator:Random(-3.14, 3.14)

	local scaleX = rRandomGenerator:Random(8.0, 12.0)

	particleCreateData.lifeFrame_ = 45
	particleCreateData.position_ = rPosition + S_Vector3(addPositionX, addPositionY, 2.0)
	particleCreateData.velocity_ = S_Vector3(addPositionX * 0.075, addPositionY * 0.075, 0.0)
	particleCreateData.startAcceleration_ = S_Vector3()
	particleCreateData.endAcceleration_ = S_Vector3()
	particleCreateData.startAngle_ = angle
	particleCreateData.endAngle_ = -angle
	particleCreateData.startWidth_ = 0.1
	particleCreateData.endWidth_ = scaleX
	particleCreateData.startHeight_ = 0.1
	particleCreateData.endHeight_ = 10.0
	particleCreateData.startColor_ = S_Vector4(1.0, 1.0, 0.8, 0.3)
	particleCreateData.endColor_ = S_Vector4(1.0, 1.0, 1.0, 0.1)

	rSmokeParticleSystem:Entry(particleCreateData)

	if nowFrame == 25 then

	return false

	end

	return true

end
