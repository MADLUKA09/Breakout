#pragma once
#include "SDL.h"

namespace Shapes {
	enum class Shape_type { Circle, Rectangle };

	class Shape
	{
	public:
		Shape(Shape_type type) { m_Type = type; }
		Shape_type getType() { return m_Type; }

		virtual int shapeWidth() = 0;
		virtual int shapeHeight() = 0;

	private:
		Shape_type m_Type;
	};

	class Rectangle : public Shape
	{
	private:
		SDL_Rect m_Rectangle;

	public:
		Rectangle(int width, int height) :Shape(Shape_type::Rectangle) {
			m_Rectangle.w = width;
			m_Rectangle.h = height;
			m_Rectangle.x = 0;
			m_Rectangle.y = 0;
		}

		void setWidth(int width) { m_Rectangle.w = width; }
		void setHeight(int height) { m_Rectangle.h = height; }

		SDL_Rect getRectangle() { return m_Rectangle; }
	
		int shapeWidth() override { return m_Rectangle.w; }
		int shapeHeight() override { return m_Rectangle.h; }
	};

	class Circle : public Shape
	{
	public:
		Circle(int radius) : m_Radius(radius), Shape(Shape_type::Circle) {}
		void setRadius(int radius) { m_Radius = radius; }
		int	 getRadius() { return m_Radius; }

		int shapeWidth() override { return m_Radius*2; }
		int shapeHeight() override { return m_Radius * 2; }

	private:
		int m_Radius;
	};

}