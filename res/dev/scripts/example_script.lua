local entity = {}
local api = {}


function init(ent, Api) 
	entity.ent = ent
	api.scene = Api:getSceneApi()

	api.scene:requestModel(ent, "dev", "lamp")

	entity.transform = api.scene:addTransform(ent)
end

function frame()

end

function update() 
	position = entity.transform:getPosition()
	position:setX(position:x() + 0.01)
	entity.transform:setPosition(position)
end

function use()
end