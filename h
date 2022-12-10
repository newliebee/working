local toggle = false
local UIS = game:GetService("UserInputService")
local Size = Vector3.new(6,6,6) --Change 2,2,2 to desired head size. Numbers represent (x,y,z).
local Key = "V" --Change C to the desired key.
local function Notify(...)
    game.StarterGui:SetCore('SendNotification',...)
end


UIS.InputBegan:Connect(function(k)
if k.KeyCode == Enum.KeyCode[Key] then
    toggle = not toggle
    for k,v in next, game:GetService('Players'):GetPlayers() do
    if v.Character:FindFirstChild('Head') then
        local Head = v.Character:FindFirstChild('Head')
        Head.Size = Vector3.new(2,1,1)
        Head.Size = Size
               v.Character.Head.Transparency = 0.3
        game.Players.LocalPlayer.Character.Head.Size = Vector3.new(2,1,1)
    if toggle then
        Head.Size = Vector3.new(2,1,1)
end
    end
    end
end
end)

Notify({Title="Hitbox Expander Loaded";Text="Toggle is V"..game.Players.LocalPlayer.Name})
local OldFunction
local tPLayer
local Event

local Hitlist = {}
local CanDamage = false
local Player = game.Players.LocalPlayer
local Ran = Random.new()

local Anim = game.Players.LocalPlayer.Character["2"].Animations.SwingLeft
local Animation = Player.Character.Humanoid:LoadAnimation(Anim)
local Module = require(game.Players.LocalPlayer.Character["2"].WeaponFunctions)
local ServerEvent = game:GetService("Players").LocalPlayer.GwyneddEventUn

local function Chance()
   return  Random:NextNumber() < 1/2 and 'Damage' or 'nDamage'
end

local function Damage(Player)
    local args = {
        [1] = "dealDamage",
        [2] = game:GetService("Players")[Player.Name].Character.Humanoid,
        [3] = game:GetService("Players").LocalPlayer.Character["2"],
        [4] = 2
    }

    ServerEvent:FireServer(unpack(args))
end

local function Check(Hit)
    for i,v in pairs(game.Players:GetChildren()) do
        if Hit:IsDescendantOf(v.Character) and v ~= game.Players.LocalPlayer then
           if CanDamage == true then
               CanDamage = false
               Damage(v)
            end
        end
    end
end

local Hook = function(self,...)
    CanDamage = true
    Event = game.Players.LocalPlayer.Character["2"].Handle.Sword.Touched:Connect(function(Hit)
        if not Hitlist[Hit.Name] then
            Check(Hit)
            Hitlist[Hit.Name] = true
        end
    end)
    delay(Animation.Length, function()
        Event:Disconnect()
        CanDamage = false
        Hitlist = {}
    end)
    return OldFunction(self,...)
end
OldFunction = hookfunction(Module.Activate, Hook)
