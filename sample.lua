-- test for hierarchical ray-tracers.
-- Thomas Pflaum 1996

gold = gr.material({0.9, 0.8, 0.4}, {0.8, 0.8, 0.4}, 25)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
blue = gr.material({0.7, 0.6, 1}, {0.5, 0.4, 0.8}, 25)
org = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
pink = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)


scene = gr.node('scene')
scene:rotate('X', 23)
scene:translate(6, -2, -15)

--[[ the arc
arc = gr.node('arc')
scene:add_child(arc)
arc:translate(0,0,-10)
arc:rotate('Y', 60)
p1 = gr.cube('p1')
arc:add_child(p1)
p1:set_material(gold)
p1:scale(0.8, 4, 0.8)
p1:translate(-2.4, 0, -0.4)

p2 = gr.cube('p2')
arc:add_child(p2)
p2:set_material(gold)
p2:scale(0.8, 4, 0.8)
p2:translate(1.6, 0, -0.4)

s = gr.sphere('s')
arc:add_child(s)
s:set_material(org)
s:scale(4, 0.6, 0.6)
s:translate(0, 3, 0)

-- the floor
plane = gr.mesh( 'plane', 'Assets/plane.obj' )
scene:add_child(plane)
plane:set_material(grass)
plane:scale(30, 30, 30)
]]--

s1 = gr.sphere( 's1' )
scene:add_child(s1)
s1:set_material(pink)
s1:scale(13, 13, 13)
s1:translate(-5, -15, 1) 

steldodec = gr.mesh( 'steldodec', 'smstdodeca.obj' )
steldodec:set_material(blue)
scene:add_child(steldodec)

--steldodec:scale(100,100,100)
steldodec:translate(100, -200, 100)
steldodec:scale(0.01, 0.01, 0.01)
steldodec:translate(-10, 0, 1)

box = gr.cube('box')
scene:add_child(box)
box:set_material(grass)
box:scale(2,1,1)
box:translate(-2,0,2)

b1 = gr.sphere( 'b1' )
scene:add_child(b1)
b1:scale(0.6, 0.6, 0.6)
b1:scale(2,1,1)
b1:rotate('Y', -40)
b1:rotate('X', 10)
b1:translate(-5, 2, 0)
b1:set_material(org)

b2 = gr.sphere( 'b2' )
b1:add_child(b2)
b2:scale(1/2,1,1)
b2:scale(0.8,1.5,1)
b2:translate(1, 1.1, 0)
b2:set_material(org)

b3 = gr.sphere( 'b3' )
b1:add_child(b3)
b3:scale(1/2,1,1)
b3:scale(1.2,2.2,1)
b3:rotate('Z', 10)
b3:translate(1.2, -2, 1)
b3:set_material(org)

b4 = gr.sphere( 'b4' )
b1:add_child(b4)
b4:scale(1/2,1,1)
b4:scale(1.2,2.2,1)
b4:rotate('Z', 10)
b4:translate(1.2, -2, -1)
b4:set_material(org)

b5 = gr.sphere( 'b5' )
b1:add_child(b5)
b5:scale(1/2,1,1)
b5:scale(1.2,2.2,1)
b5:rotate('Z', -10)
b5:translate(-1.2, -2, 1)
b5:set_material(org)

b6 = gr.sphere( 'b6' )
b1:add_child(b6)
b6:scale(1/2,1,1)
b6:scale(1.2,2.2,1)
b6:rotate('Z', -10)
b6:translate(-1.2, -2, -1)
b6:set_material(org)

b7 = gr.sphere( 'b7' )
b1:add_child(b7)
b7:scale(1/2,1,1)
b7:scale(1.5,1.1,1)
b7:translate(1.7, 2.8, 0)
b7:set_material(org)

b8 = gr.sphere( 'b8' )
b1:add_child(b8)
b8:scale(1/2,1,1)
b8:scale(1.2,2.2,1)
b8:rotate('Z', 7)
b8:translate(0.8, 4.8, 0.4)
b8:set_material(org)

b9 = gr.sphere( 'b9' )
b1:add_child(b9)
b9:scale(1/2,1,1)
b9:scale(1.2,2.2,1)
b9:rotate('Z', 7)
b9:translate(0.8, 4.8, -0.4)
b9:set_material(org)

b10 = gr.sphere( 'b10' )
b1:add_child(b10)
b10:scale(1/2,1,1)
b10:scale(0.8,1.5,1)
b10:rotate('Z', 10)
b10:translate(-1.3, 1.1, 0)
b10:set_material(org)

b11 = gr.sphere( 'b11' )
b10:add_child(b11)
b11:scale(1/0.8,1/1.5,1)
b11:scale(0.1,0.5,0.1)
--b11:rotate('Z', 10)
b11:translate(0, 1.2, 0)
b11:set_material(org)

b12 = gr.mesh( 'b12' , 'cylinder.obj')
b7:add_child( b12 )
b12:scale(0.2,1,0.2)
b12:rotate('Z', -90)
b12:translate(0.4, 0, 0)
b12:set_material(org)

b13 = gr.mesh( 'b13' , 'cylinder.obj')
b7:add_child( b13 )
b13:scale(0.3,0.2,0.3)
b13:rotate('Z', -90)
b13:translate(1.2, 0, 0)
b13:set_material(org)

--[[ sphere
poly = gr.mesh( 'poly', 'Assets/dodeca.obj' )
scene:add_child(poly)
poly:translate(-2, 1.618034, 0)
poly:set_material(blue)
]]--


-- The lights
w = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
o = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})
--l1 = gr.light({200,200,400}, {0.8, 0.8, 0.8}, {1, 0, 0})
--l2 = gr.light({0, 5, -20}, {0.4, 0.4, 0.8}, {1, 0, 0})

gr.render(scene, 'sample.png', 500, 500, 
	  {0, 0, 0,}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.4, 0.4, 0.4}, {w, o})
