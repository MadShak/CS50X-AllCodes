--[[
    GD50 2018
    Pong Remake

    *CS50 -- SHAK -- 2020 VERSION*

    Original Author: Colton Ogden
    cogden@cs50.harvard.edu

    Originally programmed by Atari in 1972. Features two
    paddles, controlled by players, with the goal of getting
    the ball past your opponent's edge. First to 10 points wins.

    This version is built to more closely resemble the NES than
    the original Pong machines or the Atari 2600 in terms of
    resolution, though in widescreen (16:9) so it looks nicer on
    modern systems.
]]

push = require 'push'
Class = require 'class'
require 'Paddle'
require 'Ball'

WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

PADDLE_SPEED = 200

BALL_SPEED = 150


function love.load()

  love.graphics.setDefaultFilter('nearest', 'nearest')

  love.window.setTitle('Pong')

  math.randomseed(os.time())

  smallFont = love.graphics.newFont('font.ttf', 8)
  largeFont = love.graphics.newFont('font.ttf', 16)
  scoreFont = love.graphics.newFont('font.ttf', 32)
  love.graphics.setFont(smallFont)


  sounds = {
    ['paddle_hit'] = love.audio.newSource('sounds/paddle_hit.wav', 'static'),
    ['score'] = love.audio.newSource('sounds/score.wav', 'static'),
    ['wall_hit'] = love.audio.newSource('sounds/wall_hit.wav', 'static')
  }


  push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
    fullscreen = false,
    resizable = true,
    vsync = true
  })


  player1 = Paddle(10, 30, 5, 20)
  player2 = Paddle(VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 30, 5, 20)


  ball = Ball(VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 4, 4)


  player1Score = 0
  player2Score = 0


  servingPlayer = 1


  winningPlayer = 0


  gameState = 'start'

  debug = false;

  p1AI = true;
  p2AI = true;
end

function love.resize(w, h)
  push:resize(w, h)
end

function love.update(dt)
  if gameState == 'serve' then

  player1 = Paddle(10, 30, 5, 20)
  player2 = Paddle(VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 30, 5, 20)


    ball.dy = math.random(-50, 50)

    if servingPlayer == 1 then
      ball.dx = BALL_SPEED
    else
      ball.dx = -BALL_SPEED
    end
  elseif gameState == 'play' then

  if p1AI == false then

    predict(ball, player1, dt)
    if love.keyboard.isDown('w') then
      player1.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('s') then
      player1.dy = PADDLE_SPEED
    else
      player1.dy = 0
    end
  else
    player1:auto(ball, PADDLE_SPEED, dt)
  end

  if p2AI == false then

    predict(ball, player2, dt)
    if love.keyboard.isDown('up') then
      player2.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('down') then
      player2.dy = PADDLE_SPEED
    else
      player2.dy = 0
    end
  else
    player2:auto(ball, PADDLE_SPEED, dt)
  end


    if ball:collides(player1) then

      local bounce = math.floor(calculateCollision(ball, player1))
      ball.acceleration = calculateAcceleration(ball, player1)

      if(ball.acceleration == 0) then
        if(ball.dx > 0) then
          ball.dx = -BALL_SPEED
        else
          ball.dx = BALL_SPEED
        end
      else
        ball.dx = -ball.dx * ball.acceleration
      end

      ball.x = player1.x + 5

      if ball.dy < 0 then
        ball.dy = - bounce
      else
        ball.dy = bounce
      end

      sounds['paddle_hit']:play()
    end


    if ball:collides(player2) then

      local bounce = math.floor(calculateCollision(ball, player2))
      ball.acceleration = calculateAcceleration(ball, player2)

      if(ball.acceleration == 0) then
        if(ball.dx > 0) then
          ball.dx = -BALL_SPEED
        else
          ball.dx = BALL_SPEED
        end
      else
        ball.dx = -ball.dx * ball.acceleration
      end

      ball.x = player2.x - 4

      if ball.dy < 0 then
        ball.dy = -bounce
      else
        ball.dy = bounce
      end

      sounds['paddle_hit']:play()
    end


    if ball.y <= 0 then
      ball.y = 0
      ball.dy = -ball.dy
      sounds['wall_hit']:play()
    end

    if ball.y >= VIRTUAL_HEIGHT - 4 then
      ball.y = VIRTUAL_HEIGHT - 4
      ball.dy = -ball.dy
      sounds['wall_hit']:play()
    end

    if ball.x < 0 then
      servingPlayer = 1
      player2Score = player2Score + 1
      sounds['score']:play()


    if player2Score == 10 then
        winningPlayer = 2
        gameState = 'done'
      else
        gameState = 'serve'

        ball:reset()
      end
    end


    if ball.x > VIRTUAL_WIDTH then
      servingPlayer = 2
      player1Score = player1Score + 1
      sounds['score']:play()


      if player1Score == 10 then
        winningPlayer = 1
        gameState = 'done'
      else
        gameState = 'serve'

        ball:reset()
      end
    end
  end


  if gameState == 'play' then
    ball:update(dt)
  end

  player1:update(dt)
  player2:update(dt)
end


function love.keypressed(key)

  if key == 'escape' then

    love.event.quit()


  elseif key == 'enter' or key == 'return' then

    if gameState == 'start' then
      gameState = 'serve'

    elseif gameState == 'serve' then
      gameState = 'play'

    elseif gameState == 'done' then
      gameState = 'serve'

      ball:reset()

      player1Score = 0
      player2Score = 0

      if winningPlayer == 1 then
        servingPlayer = 2

      else

        servingPlayer = 1

      end

    end

  elseif key == 'd' then

    if debug == false then
      debug = true

    else

      debug = false

    end

  end

end


function love.draw()
  push:apply('start')

  if gameState == 'start' then

    love.graphics.setFont(smallFont)
    love.graphics.printf('WELCOME TO PONG!', 0, 10, VIRTUAL_WIDTH, 'center')
    love.graphics.printf('Press Enter to begin!', 0, 25, VIRTUAL_WIDTH, 'center')
    love.graphics.printf('Press D to enable debug mode!', 0, 55, VIRTUAL_WIDTH, 'center')
    love.graphics.printf('Press ESC to stop!', 0, 35, VIRTUAL_WIDTH, 'center')
  elseif gameState == 'serve' then

    love.graphics.setFont(smallFont)
    love.graphics.printf('Player ' .. tostring(servingPlayer) .. "'s serve!",
    0, 10, VIRTUAL_WIDTH, 'center')
    love.graphics.printf('Press Enter to start!', 0, 20, VIRTUAL_WIDTH, 'center')
    
  elseif gameState == 'play' then

  elseif gameState == 'done' then

    love.graphics.setFont(largeFont)
    love.graphics.printf('Player ' .. tostring(winningPlayer) .. ' wins!',
    0, 10, VIRTUAL_WIDTH, 'center')
    love.graphics.setFont(smallFont)
    love.graphics.printf('Press Enter to restart!', 0, 30, VIRTUAL_WIDTH, 'center')
  end

  displayScore()

  player1:render()
  player2:render()
  ball:render()

  displayAI()

  if(debug) then

    displayFPS()

    displayDebugInfo(player1, player2, ball)
  end

  push:apply('end')
end


function displayAI()

  love.graphics.setFont(smallFont)
  love.graphics.setColor(0, 255, 0)
  love.graphics.print('P1: AI enabled', 10, VIRTUAL_HEIGHT -10)
  love.graphics.print('P2: AI enabled', VIRTUAL_WIDTH - 80, VIRTUAL_HEIGHT -10)
end

function displayScore()

  love.graphics.setFont(scoreFont)
  love.graphics.setColor(0, 1, 0, 1)
  love.graphics.print(tostring(player1Score), VIRTUAL_WIDTH / 2 - 50,
  VIRTUAL_HEIGHT / 3)
  love.graphics.print(tostring(player2Score), VIRTUAL_WIDTH / 2 + 30,
  VIRTUAL_HEIGHT / 3)
end


function displayFPS()

  love.graphics.setFont(smallFont)
  love.graphics.setColor(0, 255, 0)
  love.graphics.print('FPS: ' .. tostring(love.timer.getFPS()), 10, 10)
end

function displayDebugInfo(paddle1, paddle2, ball)
  love.graphics.setFont(smallFont)
  love.graphics.setColor(0, 255, 0)
  love.graphics.printf('Paddle 1: ('..paddle1.y..')', 0, 10, VIRTUAL_WIDTH-5, 'right')
  love.graphics.printf('Paddle 2: ('..paddle2.y..')', 0, 20, VIRTUAL_WIDTH-5, 'right')
  love.graphics.printf('Ball: ('.. ball.y ..','.. ball.x ..')', 0, 30, VIRTUAL_WIDTH-5, 'right')
  love.graphics.printf('Paddle 1 dy: ('.. math.abs(paddle1.momentum) ..')', 0, 40, VIRTUAL_WIDTH-5, 'right')

  love.graphics.line(ball.x, (ball.y + ball.height / 2), paddle1.x, (paddle1.y + paddle1.height/2 ))
  love.graphics.line(ball.x, (ball.y + ball.height / 2), paddle2.x, (paddle2.y + paddle2.height/2 ))
end

function calculateCollision(ball, paddle)
  halfBallY = ball.y + ball.height / 2
  halfPaddleY = paddle.y + paddle.height / 2

  if (halfBallY <= paddle.y or halfBallY >= paddle.y) then
    collisionValue = math.abs( (halfBallY - halfPaddleY) / (paddle.height/2) )
  else
    collisionValue = 1
  end
  collisionValue = collisionValue * 150
  collisionValue = collisionValue + 1
  return collisionValue
end

function calculateAcceleration(ball, paddle)
  if(paddle.momentum == 0) then
    return 0
  else
    return (1 + paddle.momentum / 10)
  end
end
