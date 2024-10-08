#pragma once

#include "DrawDebugHelpers.h"
// Helper macro to draw a sphere at the given location
#define DRAW_SPHERE(Location, Radius, Color) if (GetWorld()) { DrawDebugSphere(GetWorld(), Location, Radius, 16, Color, true, -1, 0, 1); }
#define DRAW_SPHERE_SingleFrame(Location, Radius, Color) if (GetWorld()) { DrawDebugSphere(GetWorld(), Location, Radius, 16, Color, false, -1, 0, 1); }

#define DRAW_LINE(Start, End, Color) if (GetWorld()) { DrawDebugLine(GetWorld(), Start, End, Color, true, -1.f, 0, 1.f); }
#define DRAW_LINE_SingleFrame(Start, End, Color) if (GetWorld()) { DrawDebugLine(GetWorld(), Start, End, Color, false, -1.f, 0, 1.f); }

#define DRAW_POINT(Location, Color) if (GetWorld()) { DrawDebugPoint(GetWorld(), Location, 10.f, Color, true, -1.f, 0); }
#define DRAW_POINT_SingleFrame(Location, Color) if (GetWorld()) { DrawDebugPoint(GetWorld(), Location, 10.f, Color, false, -1.f, 0); }

#define DRAW_VECTOR(StartLocation, EndLocation, Color) if (GetWorld()) \
{ \
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, Color, true, -1.f, 0, 1.f); \
	DrawDebugPoint(GetWorld(), EndLocation, 10.f, Color, true, -1.f, 0); \
}

#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation, Color) if (GetWorld()) \
{ \
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, Color, false, -1.f, 0, 1.f); \
	DrawDebugPoint(GetWorld(), EndLocation, 10.f, Color, false, -1.f, 0); \
}

#define DEBUG_PRINT(Format, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__)); }