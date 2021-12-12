--[[
    GD50 2018
    Pong Remake

    *CS50 -- SHAK -- 2020 VERSION*

    Author: Colton Ogden
    cogden@cs50.harvard.edu

    Represents a paddle that can move up and down. Used in the main
    program to deflect the ball back toward the opponent.
]]

Paddle = Class{}


function Paddle:init(x, y, width, height)
    self.x = x
    self.y = y
    self.width = width
    self.height = height
    self.dy = 0
    self.momentum = 0
    self.dyOld=0;
    self.yOld = self.y;
end

function Paddle:update(dt)
    
    if self.dy < 0 then
        self.y = math.max(0, self.y + self.dy * dt)
    
    else
        self.y = math.min(VIRTUAL_HEIGHT - self.height, self.y + self.dy * dt)
    end

    if(self.dyOld ~= self.dy or self.dy == 0 or self.yOld == self.y) then
        self.momentum = 0
    else 
        self.momentum = self.momentum+1
    end
    
    self.dyOld = self.dy
    self.yOld = self.y
end

function Paddle:auto(ball, PADDLE_SPEED, dt)
    self.dy = 0

    if not paddleWillHitBall(self, dt) and ballPredicted then
        if (ballPredicted.y < self.y) then
            self.dy = -PADDLE_SPEED
        elseif ( (ballPredicted.y + ball.height) > (self.y + self.height)) then
            self.dy = PADDLE_SPEED
        end
    end
end

paddleWillHitBall = function(paddle, dt)
    halfWidth = (math.floor(VIRTUAL_WIDTH / 2) - 1 )

    if ( ( paddle.x < halfWidth ) and ( ball.dx > 0 ) ) or ( paddle.x >= halfWidth ) and ( ball.dx < 0 ) then

        return true
    end

    predict(ball, paddle, dt)

    if(ballPredicted) then
        if ((ballPredicted.y < paddle.y) or (ballPredicted.y + ball.height > paddle.y + paddle.height)) then
            return false
        else
            return true
        end

    end
end

function predict(ball, paddle, dt)

    if(not ballPredicted) then

        ballPredicted = shallowcopy(ball)

            while(ballPredicted.x > paddle.x + paddle.width or ballPredicted.x + ballPredicted.width < paddle.x) do
                ballPredicted.x = ballPredicted.x + ballPredicted.dx * dt
                ballPredicted.y = ballPredicted.y + ballPredicted.dy * dt

                if ballPredicted.y <= 0 then

                    ballPredicted.y = 0
                    ballPredicted.dy = -ballPredicted.dy
                end

                if ballPredicted.y >= VIRTUAL_HEIGHT - 4 then

                    ballPredicted.y = VIRTUAL_HEIGHT - 4
                    ballPredicted.dy = -ballPredicted.dy
                end
            end
            
    else
        if (ballPredicted.dx * ball.dx < 0) then

            ballPredicted = nil
        end
    end
end


function Paddle:render()

    love.graphics.rectangle('fill', self.x, self.y, self.width, self.height)
    if(ballPredicted and debug) then
        love.graphics.setColor(255,0,0)
        love.graphics.setColor(0, 255, 0)
        love.graphics.rectangle('line', ballPredicted.x, ballPredicted.y, ballPredicted.width, ballPredicted.height)
    end
    
end

function shallowcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in pairs(orig) do
            copy[orig_key] = orig_value
        end
    else
        copy = orig
    end
    return copy
end