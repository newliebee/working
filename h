local player = game.Players.LocalPlayer
local UserInputService = game:GetService("UserInputService")

local enabled = false

getgenv()["IrisAd"] = true

UserInputService.InputBegan:Connect(function(input, gameProcessedEvent)
    if UserInputService:IsKeyDown(Enum.KeyCode.Z) then
      enabled = not(enabled)
      wait(1)
    end
end)

game:GetService("RunService").Heartbeat:Connect(function(step)
  if enabled == true then
    for _,plr in pairs(game:GetService("Players"):GetPlayers()) do
      plr.BlockingNew2.Value = not(enabled)
    end
  end
end);
