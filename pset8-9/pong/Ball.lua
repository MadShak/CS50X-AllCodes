--[[
    This is CS50 2019.
    Games Track
    Pong

    -- Ball Class --

    *CS50 -- SHAK -- 2020 VERSION*

    Author: Colton Ogden
    cogden@cs50.harvard.edu

    Represents a ball which will bounce back and forth between paddles
    and walls until it passes a left or right boundary of the screen,
    scoring a point for the opponent.
]]

Ball = Class{}

function Ball:init(x, y, width, height)
    self.x = x
    self.y = y
    self.width = width
    self.height = height
    self.dx = 0
    self.dy = 0

    self.vCenter = self.height / 2;

    self.acceleration = 0
end

function Ball:collides(paddle)
    
    if self.x > paddle.x + paddle.width or paddle.x > self.x + self.width then
        return false
    end

    
    if self.y > paddle.y + paddle.height or paddle.y > self.y + self.height then
        return false
    end 

    
    return true
end

function Ball:reset()
    self.x = VIRTUAL_WIDTH / 2 - 2
    self.y = VIRTUAL_HEIGHT / 2 - 2
    self.dx = 0
    self.dy = 0
end

function Ball:update(dt)
    self.x = self.x + self.dx * dt
    self.y = self.y + self.dy * dt
end

function Ball:render()
    love.graphics.rectangle('fill', self.x, self.y, self.width, self.height)
end