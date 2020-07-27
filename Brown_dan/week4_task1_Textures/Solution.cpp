#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class Ellipse: public IShape {
private:
  Point _pos;
  Size _size;
  shared_ptr<ITexture> _text = nullptr;
public:
    ~Ellipse() = default;

    // Возвращает точную копию фигуры.
    // Если фигура содержит текстуру, то созданная копия содержит ту же самую
    // текстуру. Фигура и её копия совместно владеют этой текстурой.
    std::unique_ptr<IShape> Clone() const override{
    	auto copy = make_unique<Ellipse>();
    	copy->SetPosition(_pos);
    	copy->SetSize(_size);
    	if (_text)
    		copy->SetTexture(_text);
    	return move(copy);
    };

	void SetPosition(Point p) override{
		_pos.x = p.x;
		_pos.y = p.y;
	};
	Point GetPosition() const override{
		return _pos;
	};

	void SetSize(Size s) override{
		_size.width = s.width;
		_size.height = s.height;
	};
	Size GetSize() const override{
		return _size;
	};

	void SetTexture(std::shared_ptr<ITexture> texture) override{
		_text = texture;
	};
	ITexture* GetTexture() const override{
		return _text.get();
	};

	// Рисует фигуру на указанном изображении
	void Draw(Image& image) const override{
		Size ts;
		Image tim;
		if(_text){
			ts = { _text->GetSize().width, _text->GetSize().height };
			tim = _text->GetImage();
		}
		// для каждой i-ой строки, которая внутри фигуры и полотна
		for(size_t i = _pos.y; (i < image.size());++i){
			if(_text && i-_pos.y < ts.height){
				// для каждого j пикселя в строке, который внутри фигуры и полотна
				for(size_t j = _pos.x;(j < image[i].size()); ++j){
					if(IsPointInEllipse(Point{j- _pos.x,i -_pos.y}, _size)){
						if(_text && j-_pos.x < ts.width)
							image[i][j] = tim[i-_pos.y][j-_pos.x];
						else
							image[i][j] = '.';
					}
				}
			}
			else{
				for(size_t j = _pos.x; (j < image[i].size()); ++j){
					if(IsPointInEllipse(Point{j- _pos.x,i -_pos.y}, _size))
						image[i][j] = '.';
				}
			}
		}
	};
};

class Rect: public IShape {
private:
  Point _pos;
  Size _size;
  shared_ptr<ITexture> _text = nullptr;
public:
    ~Rect() = default;

  // Возвращает точную копию фигуры.
  // Если фигура содержит текстуру, то созданная копия содержит ту же самую
  // текстуру. Фигура и её копия совместно владеют этой текстурой.
    std::unique_ptr<IShape> Clone() const override{
    	auto copy = make_unique<Rect>();
    	copy->SetPosition(_pos);
    	copy->SetSize(_size);
    	if (_text)
    		copy->SetTexture(_text);
    	return move(copy);
    };

	void SetPosition(Point p) override{
		_pos.x = p.x;
		_pos.y = p.y;
	};
	Point GetPosition() const override{
		return _pos;
	};

	void SetSize(Size s) override{
		_size.width = s.width;
		_size.height = s.height;
	};
	Size GetSize() const override{
		return _size;
	};

	void SetTexture(std::shared_ptr<ITexture> texture) override{
		_text = texture;
	};
	ITexture* GetTexture() const override{
		return _text.get();
	};

	// Рисует фигуру на указанном изображении
	void Draw(Image& image) const override{
		Size ts;
		Image tim;
		if(_text){
			ts = { _text->GetSize().width, _text->GetSize().height };
			tim = _text->GetImage();
		}
		// для каждой i-ой строки, которая внутри полотна и фигуры
		for(size_t i = _pos.y; i < (_size.height+_pos.y) && (i < image.size());++i){
			if(_text && i-_pos.y < ts.height){
				// для каждого j пикселя в строке, который внутри полотна и фигуры
				for(size_t j = _pos.x; (j < _size.width+_pos.x) && (j < image[i].size()); ++j){
					if(_text && j-_pos.x < ts.width)
						image[i][j] = tim[i-_pos.y][j-_pos.x];
					else
						image[i][j] = '.';
				}
			}
			else{
				for(size_t j = _pos.x; (j < _size.width+_pos.x) && (j < image[i].size()); ++j){
						image[i][j] = '.';
				}
			}
		}
	};
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	if(shape_type == ShapeType::Ellipse)
		return make_unique<Ellipse>();
	if (shape_type == ShapeType::Rectangle)
		return make_unique<Rect>();
	return nullptr;
}
