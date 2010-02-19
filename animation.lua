Animation = {}

function Animation:New(o)
	o = o or {
		__dat = {
			-- key = {},	
		},
		-- current_key = "xxx",
		x = 0,
		y = 0,
		rot = nil,
		hscale = nil,
		vscale = nil,
	}
	setmetatable(o, { __index = self })
	return o
end

function Animation:Add(key, filename, rowgrid_count, colgrid_count, begin_index, end_index)
	begin_index = begin_index or 1
	end_index = end_index or (rowgrid_count * colgrid_count)
	local nframes = end_index - begin_index + 1
	self.__dat[key]	= {}
	local animdat = self.__dat[key]
	animdat.tex = hge.Texture_Load(filename)
	animdat.width = animdat.tex:GetWidth(true)
	animdat.height = animdat.tex:GetHeight(true)
	animdat.sprwidth = animdat.width / rowgrid_count
	animdat.sprheight = animdat.height / colgrid_count
	local pos_x = ((begin_index - 1) % rowgrid_count) * animdat.sprwidth
	local pos_y = math.floor((begin_index - 1) / rowgrid_count) * animdat.sprheight
	animdat.spr = hge.NewAnimation(animdat.tex, nframes , 0, pos_x, pos_y, animdat.sprwidth, animdat.sprheight)
end

function Animation:Update(deltatime)
	if not self.current_key then return end
	deltatime = deltatime or hge.Timer_GetDelta()
	local animdat = self.__dat[self.current_key]
	animdat.spr:Update(deltatime)
	print(string.format("animation %d, frame %d", self.current_key, animdat.spr:GetFrame()))
	if not animdat.spr:IsPlaying() then
		if animdat.callback then
			animdat.callback(self, self.current_key)
		else
			self:Stop()
		end
	end
end

function Animation:Play(key, mode, fps, callback)
	self:Stop()
	local animdat = self.__dat[key]
	if not animdat then 
		error(string.format("Animation(%s) not exist", key))
	end
	print(string.format("Animation %d is playing", key))
	animdat.spr:SetMode(mode)
	animdat.spr:SetSpeed(fps)
	animdat.spr:Play()
	self.current_key = key
	animdat.callback = callback
end

function Animation:Stop()
	if not self.current_key then return end
	local animdat = self.__dat[self.current_key]
	animdat.spr:Stop()
	self.current_key = nil
end

function Animation:Move(x, y)
	self.x = self.x + x
	self.y = self.y + y
end

function Animation:MoveTo(x, y)
	self.x = x
	self.y = y
end

function Animation:Render()
	if not self.current_key then return end
	local animdat = self.__dat[self.current_key]
	animdat.spr:Render(self.x, self.y, self.rot, self.hscale, self.vscale)
end

AnimationGroup = {
	-- [Animation] = boolean (Enable) 
}

function AddToAnimationGroup(animation, enable)
	AnimationGroup[animation] = enable 
end

function AnimationGroupRender()
	for animation, enable in pairs(AnimationGroup) do
		if enable then
			animation:Render()
		end
	end
end

function AnimationList(anim, fps, list)
	local cb
	local i = 1
	cb = function (anim, key)
		if i > #list then return end
		anim:Play(list[i], 0, fps, cb)
		i = i + 1
	end
	return cb
end


