# TODO:
#  - action input buffer
#  - non-clusterfuck architecture (a proper state machine?)
#  - input abstracted so that AI could be plugged in
#  - dynamic instantiantion

extends Area2D

enum State {DEFAULT, DUCK, MIDAIR, ACTION}

const GROUND_POSITION = 560
const GRAVITY = 15
const SPEED = 250
const MAX_JUMPS = 2
const JUMP_BASE_VELOCITY = 5
const JUMP_FACTORS = [1, 0.8]

onready var ANIMATION_PLAYER = $FighterAnimationPlayer
var state = State.DEFAULT

const input_vector = Vector2()

var is_ducking = false
var vertical_velocity = 0
var jump_counter = 0
const horizontal_vector = Vector2()

func _ready():
	try_transition(State.DEFAULT)

func apply_gravity(delta):
	if position.y < GROUND_POSITION:
		vertical_velocity += GRAVITY * delta

func get_directional_input():
	input_vector.x = 0
	input_vector.y = 0
	if Input.is_action_pressed("ui_right"):
		input_vector.x += 1
	if Input.is_action_pressed("ui_left"):
		input_vector.x -= 1
	if Input.is_action_pressed("ui_down"):
		input_vector.y += 1
	if Input.is_action_pressed("ui_up"):
		input_vector.y -= 1

func process_action_input():
	if Input.is_action_just_pressed("ui_up"):
		try_transition(State.MIDAIR)
	if Input.is_action_pressed("ui_down"):
		try_transition(State.DUCK)
	elif Input.is_action_just_released("ui_down"):
		try_transition(State.DEFAULT)
	elif Input.is_action_just_pressed("action_1"):
		attack("punch")

func attack(name):
	try_transition(State.ACTION)
	match name:
		"punch":
			ANIMATION_PLAYER.play("punch")

func try_transition(new_state):
	match new_state:
		State.MIDAIR:
			if jump_counter < MAX_JUMPS:
				ANIMATION_PLAYER.play("idle")
				vertical_velocity = -JUMP_BASE_VELOCITY * JUMP_FACTORS[jump_counter]
				jump_counter += 1
		State.DUCK:
			if state != State.DEFAULT:
				return
			is_ducking = true
			ANIMATION_PLAYER.play("duck")
		State.DEFAULT:
			is_ducking = false
			ANIMATION_PLAYER.play("idle")
		State.ACTION:
			is_ducking = false
	state = new_state

func process_directional_input():
	if input_vector.length() > 0:
		input_vector = input_vector.normalized() * SPEED
		match state:
			State.DEFAULT:
				if ANIMATION_PLAYER.current_animation != "walk":
					if input_vector.x > 0:
						ANIMATION_PLAYER.play("walk")
					else:
						ANIMATION_PLAYER.play_backwards("walk")
			State.MIDAIR:
				if input_vector.x > 0:
					ANIMATION_PLAYER.play("jump-right")
				else:
					ANIMATION_PLAYER.play("jump-left")
	else:
		if state == State.DEFAULT:
			ANIMATION_PLAYER.play("idle")

func can_move_horizontally():
	if state == State.DUCK:
		return false
	if state == State.ACTION && position.y == GROUND_POSITION:
		return false
	return true

func update_position(delta):
	var new_position = position
	if can_move_horizontally():
		new_position.x = position.x + input_vector.x * delta
	new_position.y = position.y + vertical_velocity * SPEED * delta
	if new_position.y >= GROUND_POSITION:
		if state == State.MIDAIR:
			try_transition(State.DEFAULT)
		new_position.y = GROUND_POSITION
		jump_counter = 0
		vertical_velocity = 0
	position = new_position

func _process(delta):
	apply_gravity(delta)
	get_directional_input()
	process_directional_input()
	process_action_input()
	update_position(delta)

func _on_FighterAnimationPlayer_animation_finished(anim_name):
	if anim_name == "punch":
		try_transition(State.DEFAULT)
