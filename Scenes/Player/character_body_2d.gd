extends CharacterBody2D
#Enums
enum PlayerState {
	STANDBY,
	MOVING
}
#Constants
const SPEED = 100.0
const LEAN_UNIT = 5.0
const MAX_LEAN_ANGLE = 30
#Vars
var currentState = PlayerState.STANDBY
##########################################################
func _physics_process(delta: float) -> void: 
	self.move(delta)
	self.updateAnimations()
	print(rotation_degrees)
	%Label1.text = str(rotation_degrees)
	
func move(delta: float) -> void:
	"""Checks movement keys and acts accodingly"""
	# Get the input direction and handle the movement/deceleration.
	var directionX := Input.get_axis("ui_left", "ui_right")
	var directionY := Input.get_axis("ui_up", "ui_down")

	if directionX:
		velocity.x = directionX * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
	if directionY:
		velocity.y = directionY * SPEED
	else:
		velocity.y = move_toward(velocity.y, 0, SPEED)
	move_and_slide()

#func updateAnimations() -> void:
	#if velocity.length() > 0.0:
		#STATE = "moving"
	#else:
		#STATE = "standby"

func updateAnimations() -> void:
	if velocity.length() > 0.0:
		currentState = PlayerState.MOVING
		if ro
	else:
		currentState = PlayerState.STANDBY
