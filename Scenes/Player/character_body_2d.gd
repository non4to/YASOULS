extends CharacterBody2D
#Enums
enum PlayerState {
	STANDBY,
	MOVING
}
#Constants
const SPEED = 75
const MAX_LEAN_ANGLE = 10

const BREATH_SPEED = 2
const BREATH_AMP = 0.02

const MAX_INVULNERABILITY = 60
const ROLL_SPEED = 5

#Vars
var currentState = PlayerState.STANDBY
var lastMovementDir = Vector2(1,0)
var leanUnit = 3

var isRolldodging = false
var invulCounter = 0
##########################################################
func _physics_process(delta: float) -> void: 
	self.move(delta)
	self.updateAnimations()
	print(rotation_degrees)
	
	#%Label1.text = str(isRolldodging)
	
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
		
	if (Input.is_action_just_pressed("RollDodge")) and not(isRolldodging):
		velocity *= ROLL_SPEED
		isRolldodging = true

	move_and_slide()

func updateAnimations() -> void:
	var timeMs = Time.get_ticks_msec() / 1000.0 # Tempo em segundos (float)
	
	if isRolldodging:
		if velocity[0] > 0:
			#rotation_degrees += ROLL_SPEED
			%knightSprite.rotation_degrees += ROLL_SPEED
		else:
			%knightSprite.rotation_degrees -= ROLL_SPEED
		invulCounter += 1
		if invulCounter > MAX_INVULNERABILITY:
			isRolldodging = false
			invulCounter = 0
			%knightSprite.rotation_degrees = 0
	
	elif velocity.length() > 0.0:
		currentState = PlayerState.MOVING
		rotation_degrees += leanUnit
		%knightSprite.scale = Vector2(1.05,1.05)
		if (rotation_degrees > MAX_LEAN_ANGLE) or (rotation_degrees < -MAX_LEAN_ANGLE):
			leanUnit *= -1
	else:
		var breathValue = sin(timeMs * BREATH_SPEED)
		var scaleFactor = breathValue * BREATH_AMP
		var newScale = Vector2(1,1) + Vector2(0, scaleFactor)
		currentState = PlayerState.STANDBY
		rotation_degrees = 0
		%knightSprite.scale = newScale
