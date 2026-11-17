#include "REALHEROBDCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

AREALHEROBDCharacter::AREALHEROBDCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 620.f;
    GetCharacterMovement()->AirControl = 0.25f;
    GetCharacterMovement()->MaxWalkSpeed = 600.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 350.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AREALHEROBDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AREALHEROBDCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AREALHEROBDCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AREALHEROBDCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AREALHEROBDCharacter::LookUp);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AREALHEROBDCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AREALHEROBDCharacter::StopJump);
}

void AREALHEROBDCharacter::MoveForward(float Value)
{
    if (Controller && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
    }
}

void AREALHEROBDCharacter::MoveRight(float Value)
{
    if (Controller && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
    }
}

void AREALHEROBDCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void AREALHEROBDCharacter::LookUp(float Value) { AddControllerPitchInput(Value); }
void AREALHEROBDCharacter::StartJump() { Jump(); }
void AREALHEROBDCharacter::StopJump() { StopJumping(); }
