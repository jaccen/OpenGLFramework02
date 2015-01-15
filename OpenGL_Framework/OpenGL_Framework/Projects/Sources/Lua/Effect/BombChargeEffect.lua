--[[ バインドしてある関数およびクラス ]]--[[


1. S_ParticleData

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

・ void Entry(const S_ParticleData& rData);


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
・ void ResetCount();


6. C_RandomManager

・ float Random(float min = 0.0f, float max = 1.0f);


]]


--[[ 円周乱数を取得する --]]

-- double raduis
-- C_RandomManager randomManager

 function CircumferenceRandom(radius, randomManager)

	-- 2π
	local PI2 = 6.283185

	-- 角度を求める
	local angle = randomManager:Random(0.0, PI2)

	-- 各成分を設定
	local x = math.cos(angle) * radius
	local y = math.sin(angle) * radius

	return x, y

 end


--[[ ボムのチャージエフェクトのロジックを処理する --]]

--[[ 引き数 ]]

-- IC_ParticleSystem& rCircleParticleSystem
-- IC_ParticleSystem& rRingParticleSystem
-- C_FrameCounter& rFrameCounter
-- C_RandomManager& rRandomManager
-- S_Vector3 rPosition

function BombChargeEffectLogic(rCircleParticleSystem, rRingParticleSystem, rFrameCounter, rRandomManager, rPosition)

	-- パーティクルの情報
	local particleData = S_ParticleData()

	-- 現在のフレーム数
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
