using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;
using SF.Tool.Asset;

namespace SF.Tool.Builder
{
    /// <summary>
    /// Builder asset DB
    /// </summary>
    public static class BuilderAssetDB
    {
        public static AssetDataBase Instance { get; private set; }

        static BuilderAssetDB()
        {
            Instance = new AssetDataBase();
        }
        static public void RegisterClasses(Assembly assembly)
        {
            Instance.RegisterClasses(assembly);
        }

        static public Asset.Asset GetItem(string resourcePath)
        {
            return Instance.GetItem(resourcePath);
        }

        static public Asset.Asset AddOrGetAsset(string resourcePath)
        {
            return Instance.AddOrGetAsset(resourcePath);
        }
    }
    
}
