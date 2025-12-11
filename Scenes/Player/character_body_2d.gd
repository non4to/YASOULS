extends CharacterBody2D

var STATE_MOVING = false
var STATE_STANDBY = true

const SPEED = 100.0
var last_velocity_x = 0.0
#Used in animations of moving
const LEAN_FREQUENCY = 5.0
const MAX_LEAN_ANGLE = 30
const LEAN_SMOOHNESS = 0.5

func _physics_process(delta: float) -> void: 
	self.move(delta)
	self.updateAnimations()
	last_velocity_x = velocity.x
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
	# 1. Checa o estado de movimento
	if velocity.length() > 0.0:
		STATE_MOVING = true
		STATE_STANDBY = false
	else:
		STATE_MOVING = false
		STATE_STANDBY = true

	var is_moving = velocity.length() > 0.0 # Usando uma variável local é mais limpo

	if is_moving:
		# 1. Calcular a rotação alvo usando a função seno
		# O tempo do jogo (Time.get_ticks_msec() ou Time.get_time_started_sec()) 
		# multiplicado pela frequência cria a onda.
		# O resultado (entre -1 e 1) é multiplicado pelo ângulo máximo.
		var sine_wave = sin(Time.get_time_started_sec() * LEAN_FREQUENCY)
		var target_rotation = MAX_LEAN_ANGLE * sine_wave
		
		# 2. Aplicar a rotação de forma suave
		# O LEAN_SMOOTHNESS alto (0.8) garante que o sprite siga a onda rapidamente.
		rotation = lerp_angle(rotation, target_rotation, LEAN_SMOOTHNESS)
	else:
		# Quando parado, retorna suavemente para 0 graus
		rotation = lerp_angle(rotation, 0.0, LEAN_SMOOTHNESS)
