local entity = {}


function init(ent) 
	entity.ent = ent
	scene:addTransform(entity)
	scene:addModel(entity, [pack = "dev", model = "lamp"])
end

function frame()
  
end

function update() 

end

function use()
end