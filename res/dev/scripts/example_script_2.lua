local entity = {}
local api = {}


function init(ent, Api) 
	entity.ent = ent
	api.scene = Api:getSceneApi()
	api.registry = api.scene:getRegistry()
	api.scene:requestModel(ent, "dev", "lamp")

	api.registry:addTransform(ent)
end

function frame() end

function update() 
	transform = api.registry:getTransform(entity.ent)
	position = transform:getPosition()
	position:setY(position:y() + 0.01)
end

function use()
end