extends CharacterBody2D
#region Initialize
# Enums
enum PlayerState {
	IDLE,
	MOVING,
	ATTACKING,
	ROLLING,
	TAKING_DAMAGE,
}

# Constants
const SPEED:float = 50
const MAX_LEAN_ANGLE:float = 10

const BREATH_SPEED:float = 2
const BREATH_AMP:float = 0.02

const ROLL_DURATION:float = 0.3
const ROLL_SPEED:float = 200
const ROLL_ANIMATION_SPEED:float = 20
# Variables
var currentState = PlayerState.IDLE
var lastMovementDir:Vector2 = Vector2(1,0)
var leanUnit:float = 3

var rollDirection:Vector2 = Vector2.ZERO
var dodgeRollTimer:float = 0
var invulnerable:bool = false

var currentWeapon = null
#endregion
##########################################################
func _physics_process(delta: float) -> void: 
	var inputDirection = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")

	match currentState:
		PlayerState.IDLE:
			do_idle_state(delta, inputDirection)
		PlayerState.MOVING:
			do_moving_state(delta, inputDirection)
		PlayerState.ROLLING:
			do_roll_state(delta)
	
	move_and_slide()
	updateAnimations()	
	print(invulnerable)
	#%Label1.text = str(isRolldodging)
	
func do_idle_state(delta, inputDirection: Vector2):
	velocity = Vector2.ZERO
	if inputDirection != Vector2.ZERO:
		currentState = PlayerState.MOVING
		do_moving_state(delta, inputDirection)
	check_roll(inputDirection)
	
func do_moving_state(delta, inputDirection: Vector2):
	velocity = lerp(velocity, inputDirection * SPEED, 22.0 * delta)
	if inputDirection == Vector2.ZERO:
		velocity = Vector2.ZERO
		currentState = PlayerState.IDLE
	else:
		lastMovementDir = inputDirection
	check_roll(inputDirection)

func do_roll_state(delta):
	dodgeRollTimer += delta
	var elapsedPercent = 1 - (dodgeRollTimer/ROLL_DURATION)
	var dodgeSpeed = lerp(ROLL_SPEED, ROLL_SPEED * 0.5, elapsedPercent)
	velocity = rollDirection * dodgeSpeed
	
	if dodgeRollTimer >= ROLL_DURATION:
		currentState = PlayerState.IDLE
		rollDirection = Vector2.ZERO
		invulnerable = false

func check_roll(inputDirection: Vector2):
	if Input.is_action_just_pressed("RollDodge") and (currentState != PlayerState.ROLLING):
		currentState = PlayerState.ROLLING
		invulnerable = true
		dodgeRollTimer = 0
		if inputDirection != Vector2.ZERO:
			rollDirection = inputDirection
		else:
			rollDirection = lastMovementDir
		velocity = rollDirection * ROLL_SPEED

func updateAnimations() -> void:
	var timeMs = Time.get_ticks_msec() / 1000.0 # Tempo em segundos (float)
	
	match currentState:
		PlayerState.IDLE:
			%knightSprite.rotation_degrees = 0
			var breathValue = sin(timeMs * BREATH_SPEED)
			var scaleFactor = breathValue * BREATH_AMP
			var newScale = Vector2(1,1) + Vector2(0, scaleFactor)
			currentState = PlayerState.IDLE
			rotation_degrees = 0
			%knightSprite.scale = newScale

		PlayerState.MOVING:
			%knightSprite.rotation_degrees = 0
			rotation_degrees += leanUnit
			%knightSprite.scale = Vector2(1.05,1.05)
			if (rotation_degrees > MAX_LEAN_ANGLE) or (rotation_degrees < -MAX_LEAN_ANGLE):
				leanUnit *= -1

		PlayerState.ROLLING:
			if velocity[0] > 0:
				#rotation_degrees += ROLL_SPEED
				%knightSprite.rotation_degrees += ROLL_ANIMATION_SPEED
			else:
				%knightSprite.rotation_degrees -= ROLL_ANIMATION_SPEED
