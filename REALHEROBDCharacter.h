#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "REALHEROBDCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class REALHEROBD_API AREALHEROBDCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AREALHEROBDCharacter();

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void StartJump();
    void StopJump();
};
